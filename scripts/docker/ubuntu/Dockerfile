FROM ubuntu:focal

env DEBIAN_FRONTEND noninteractive

RUN apt -y  update && apt install -y \
   git sudo curl clang gcc g++ make unzip python m4 wget \ 
   nasm libacl1-dev  libncurses-dev libbz2-dev   \
   libglu1-mesa-dev  libxxf86vm-dev libxkbfile-dev libxext-dev libxt-dev libfontconfig1-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libsdl2-2.0-0 \
    libgl1-mesa-dev  mesa-utils mesa-utils-extra ragel libgtk-3-dev libharfbuzz0b \
  && curl -sL https://deb.nodesource.com/setup_12.x -o /node_setup.sh \
  && chmod +x /node_setup.sh && /node_setup.sh \
  && apt install -y nodejs  \
  && rm -rf /var/lib/apt/lists/*

RUN npm install -g esy@latest --unsafe-perm=true && npm install -g node-gyp
