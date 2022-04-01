[![Build Status Stable](https://github.com/santilococo/oni2/actions/workflows/stable.yml/badge.svg)](https://github.com/santilococo/oni2/actions/workflows/main.yml)
[![Build Status Nightly](https://github.com/santilococo/oni2/actions/workflows/nightly.yml/badge.svg)](https://github.com/santilococo/oni2/actions/workflows/main.yml)
[![Discord](https://img.shields.io/discord/417774914645262338.svg)](https://discord.gg/7maEAxV)

# Onivim 2

This is a fork of [Onivim 2](https://github.com/onivim/oni) where I will automatically upload the latest builds when a new version of `onivim2` is released.

## Download (for Linux)

### Arch-based distributions

Download the AUR package [onvim2-bin](https://aur.archlinux.org/packages/onivim2-bin) with the AUR helper of your choice. 

### Other distributions

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

You can automatically download `AppDir.tar` (from the stable release) clicking this [hyperlink](https://github.com/santilococo/oni2/releases/download/v0.5.7/AppDir.tar). 

## Documentation

See [README](https://github.com/onivim/oni2#onivim-2).

## License

Onivim 2 source code is licensed under the [MIT](LICENSE.md) license.

#### Third-Party Code

Several dependencies have their own set of license terms here: [ThirdPartyLicenses.txt](ThirdPartyLicenses.txt)
