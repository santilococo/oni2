[![Discord](https://img.shields.io/discord/417774914645262338.svg)](https://discord.gg/7maEAxV)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Onivim 2

This is a fork of [Onivim 2](https://github.com/onivim/oni2) where I will upload the latest builds (both stable and nightly).

## Table of Contents
* [Download (for Linux)](#download)
  - [Arch-based distributions](#download-arch)
  - [Other distributions](#download-other)
* [Documentation](#documentation)
* [License](#license)

## Download (for Linux) <a name="download"></a>

### Arch-based distributions <a name="download-arch"></a>

Download [onvim2-bin](https://aur.archlinux.org/packages/onivim2-bin) or [onivim2-nightly-bin](https://aur.archlinux.org/packages/onivim2-nightly-bin) with the AUR helper of your choice. 

### Other distributions <a name="download-other"></a>

First, you need to download `Onivim2-x86_64.AppImage` from [releases](https://github.com/santilococo/oni2/releases), which is the AppImage of `onivim2`. You can choose the stable or the nightly release. 

Then, if you want `Oni2` to appear in your application menu/launcher, you need to download the [desktop file](https://raw.githubusercontent.com/santilococo/oni2/master/scripts/linux/Onivim2.desktop) and [logo](https://raw.githubusercontent.com/santilococo/oni2/master/assets/images/logo.png).

Finally, you need to move the files to `/usr` (you may need root privileges):

```bash
chmod u+x Onivim2-x86_64.AppImage
mv Onivim2-x86_64.AppImage /usr/local/bin/Oni2
```

And if you also downloaded the desktop file and logo:

```bash
mv Onivim2.desktop /usr/share/applications
mv logo.png /usr/share/icons/Onivim2.png
```

After that, if `/usr/local/bin` is in your `PATH`, you can simply run `Oni2` in your terminal or application launcher.

## Documentation <a name="documentation"></a>

See [Documentation](https://github.com/onivim/oni2#documentation).

## License <a name="license"></a>

See [LICENSE](LICENSE.md) and [ThirdPartyLicenses](ThirdPartyLicenses.txt).
