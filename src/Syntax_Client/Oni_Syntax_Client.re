/*
 Syntax client
 */

open EditorCoreTypes;
open Oni_Core;
open Oni_Core.Utility;

module Transport = Exthost.Transport;
module NamedPipe = Exthost.NamedPipe;
module Packet = Exthost.Transport.Packet;

open Oni_Syntax;
module Protocol = Oni_Syntax.Protocol;
module ServerToClient = Protocol.ServerToClient;

module ClientLog = (val Log.withNamespace("Oni2.Syntax.Client"));
module ServerLog = (val Log.withNamespace("Oni2.Syntax.Server"));

module Defaults = {
  let executableName = "Oni2_editor" ++ (Sys.win32 ? ".exe" : "");
  let executablePath = Revery.Environment.executingDirectory ++ executableName;
};

type t = {
  transport: Transport.t,
  process: Luv.Process.t,
  nextId: ref(int),
};

let writeTransport =
    (~id=0, transport: Transport.t, msg: Protocol.ClientToServer.t) => {
  let bytes = Marshal.to_bytes(msg, []);
  let packet = Transport.Packet.create(~packetType=Regular, ~id, bytes);
  Transport.send(~packet, transport);
};

let write = ({transport, nextId, _}: t, msg: Protocol.ClientToServer.t) => {
  incr(nextId);
  let id = nextId^;
  writeTransport(~id, transport, msg);
};

let startProcess = (~executablePath, ~namedPipe, ~parentPid, ~onClose) => {
  let arg = "--syntax-highlight-service=" ++ parentPid ++ ":" ++ namedPipe;
  ClientLog.debugf(m =>
    m(
      "Starting executable: %s and parentPid: %s with args: %s",
      executablePath,
      parentPid,
      arg,
    )
  );

  let on_exit = (_proc, ~exit_status, ~term_signal) => {
    let exitCode = exit_status |> Int64.to_int;
    if (exitCode == 0) {
      ClientLog.debug("Syntax process exited safely.");
    } else {
      ClientLog.errorf(m =>
        m(
          "Syntax process exited with code: %d and signal: %d",
          exitCode,
          term_signal,
        )
      );
    };
    onClose(exitCode);
  };

  LuvEx.Process.spawn(~on_exit, executablePath, [executablePath, arg])
  |> Result.map_error(Luv.Error.strerror);
};

let start =
    (
      ~parentPid=?,
      ~executablePath=Defaults.executablePath,
      ~onConnected=() => (),
      ~onClose=_ => (),
      ~onHighlights,
      ~onHealthCheckResult,
      grammarInfo,
      setup,
    ) => {
  let parentPid =
    switch (parentPid) {
    | None => Luv.Pid.getpid() |> string_of_int
    | Some(pid) => pid
    };

  let namedPipe = Protocol.pidToNamedPipe(parentPid);
  let handleMessage = msg =>
    switch (msg) {
    | ServerToClient.Initialized =>
      ClientLog.info("Initialized");
      onConnected();
    | ServerToClient.EchoReply(result) =>
      ClientLog.tracef(m => m("got message from channel: |%s|", result))
    | ServerToClient.Log(msg) => ServerLog.trace(msg)
    | ServerToClient.Closing => ServerLog.debug("Closing")
    | ServerToClient.HealthCheckPass(res) => onHealthCheckResult(res)
    | ServerToClient.TokenUpdate({bufferId, tokens}) =>
      ClientLog.info("Received token update");
      onHighlights(~bufferId, ~tokens);
      ClientLog.trace("Tokens applied");
    };

  let handlePacket = bytes => {
    let msg: ServerToClient.t = Marshal.from_bytes(bytes, 0);
    handleMessage(msg);
  };

  let _transport = ref(None);

  let dispatch =
    fun
    | Transport.Connected => {
        ClientLog.info("Connected to server");
        _transport^
        |> Option.iter(t =>
             writeTransport(
               ~id=0,
               t,
               Protocol.ClientToServer.Initialize(grammarInfo, setup),
             )
           );
      }
    | Transport.Error(msg) => ClientLog.errorf(m => m("Error: %s", msg))
    | Transport.Disconnected => ClientLog.info("Disconnected")
    | Transport.Received({body, _}) => handlePacket(body);

  Transport.start(~namedPipe, ~dispatch)
  |> Utility.ResultEx.tap(transport => _transport := Some(transport))
  |> Utility.ResultEx.flatMap(transport => {
       startProcess(~executablePath, ~namedPipe, ~parentPid, ~onClose)
       |> Result.map(process => {transport, process, nextId: ref(0)})
     });
};

let startHighlightingBuffer =
    (
      ~bufferId: int,
      ~scope: string,
      ~visibleRanges: list(Range.t),
      ~lines: array(string),
      v: t,
    ) => {
  let message: Oni_Syntax.Protocol.ClientToServer.t =
    BufferStartHighlighting({bufferId, scope, lines, visibleRanges});
  ClientLog.tracef(m => m("Sending startHighlightingBuffer: %d", bufferId));
  write(v, message);
};

let stopHighlightingBuffer = (~bufferId: int, v: t) => {
  write(v, BufferStopHighlighting(bufferId));
  ClientLog.tracef(m => m("Sending stopHighlightingBuffer: %d", bufferId));
};

let notifyThemeChanged = (v: t, theme: TokenTheme.t) => {
  ClientLog.info("Notifying theme changed.");
  write(v, Protocol.ClientToServer.ThemeChanged(theme));
};

let notifyTreeSitterChanged = (~useTreeSitter: bool, v: t) => {
  ClientLog.infof(m => m("Notifying treeSitter changed: %b", useTreeSitter));
  write(v, Protocol.ClientToServer.UseTreeSitter(useTreeSitter));
};

let healthCheck = (v: t) => {
  write(v, Protocol.ClientToServer.RunHealthCheck);
};

let notifyBufferUpdate = (~bufferUpdate: BufferUpdate.t, v: t) => {
  ClientLog.trace("Sending bufferUpdate notification...");
  write(v, Protocol.ClientToServer.BufferUpdate(bufferUpdate));
};

let notifyBufferVisibilityChanged =
    (~bufferId: int, ~ranges: list(Range.t), v: t) => {
  ClientLog.trace("Sending visibleRangesChanged notification...");
  write(
    v,
    Protocol.ClientToServer.BufferVisibilityChanged({bufferId, ranges}),
  );
};

let close = (syntaxClient: t) => {
  ClientLog.debug("Sending close request...");
  write(syntaxClient, Protocol.ClientToServer.Close);
};

module Testing = {
  let simulateReadException = ({transport, _}: t) => {
    let id = 1;
    let bytes = Bytes.make(128, 'a');
    let packet = Transport.Packet.create(~packetType=Regular, ~id, bytes);
    ClientLog.trace("Simulating a bad packet...");
    Transport.send(~packet, transport);
  };

  let simulateMessageException = (v: t) => {
    ClientLog.trace("Sending simulateMessageException notification...");
    write(v, Protocol.ClientToServer.SimulateMessageException);
  };
};
