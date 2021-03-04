
Debian
====================
This directory contains files used to package tecsacoind/tecsacoin-qt
for Debian-based Linux systems. If you compile tecsacoind/tecsacoin-qt yourself, there are some useful files here.

## tecsacoin: URI support ##


tecsacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tecsacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your tecsacoinqt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

tecsacoin-qt.protocol (KDE)

