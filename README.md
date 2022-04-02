[![Build Status Stable](https://github.com/santilococo/oni2/actions/workflows/stable.yml/badge.svg)](https://github.com/santilococo/oni2/actions/workflows/main.yml)
[![Build Status Nightly](https://github.com/santilococo/oni2/actions/workflows/nightly.yml/badge.svg)](https://github.com/santilococo/oni2/actions/workflows/main.yml)
[![Discord](https://img.shields.io/discord/417774914645262338.svg)](https://discord.gg/7maEAxV)

# Onivim 2

This is a fork of [Onivim 2](https://github.com/onivim/oni) where I will upload the latest builds (both stable and nightly).

## Table of Contents
* [Download (for Linux)](#download)
  - [Arch-based distributions](#download-arch)
  - [Other distributions](#download-other)
* [Documentation](#documentation)
* [License](#license)

## Download (for Linux) <a name="download"></a>

### Arch-based distributions <a name="download-arch"></a>

Download the AUR package [onvim2-bin](https://aur.archlinux.org/packages/onivim2-bin) with the AUR helper of your choice. 

### Other distributions <a name="download-other"></a>

First, you need to download `AppDir.tar` from [releases](https://github.com/santilococo/oni2/releases) which contains the AppDir of `onivim2`. You can choose the stable release or the nightly release. 

Then, to build the AppImage, you need to download [appimagetool](https://appimage.github.io/appimagetool) and run:
```
tar -xf AppDir.tar
cd _release
ARCH=x86_64 appimagetool Onivim2.AppDir
```

Finally, you need to move some files to `/usr` (you may need root privileges):
```
mv Onivim2-x86_64.AppImage /usr/local/bin/Oni2
mv Onivim2.AppDir/Onivim2.desktop /usr/share/applications
mv Onivim2.AppDir/Onivim2.png /usr/share/icons
```

## Documentation <a name="documentation"></a>

See [Documentation](https://github.com/onivim/oni2#documentation).

## License <a name="license"></a>

Onivim 2 source code is licensed under the [MIT](LICENSE.md) license.

#### Third-Party Code

Several dependencies have their own set of license terms here: [ThirdPartyLicenses.txt](ThirdPartyLicenses.txt)
