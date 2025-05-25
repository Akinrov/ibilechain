
Debian
====================
This directory contains files used to package ibilechaind/ibilechain-qt
for Debian-based Linux systems. If you compile ibilechaind/ibilechain-qt yourself, there are some useful files here.

## ibilechain: URI support ##


ibilechain-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ibilechain-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ibilechain-qt binary to `/usr/bin`
and the `../../share/pixmaps/ibilechain128.png` to `/usr/share/pixmaps`

ibilechain-qt.protocol (KDE)

