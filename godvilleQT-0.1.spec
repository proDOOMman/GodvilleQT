Summary: Simple client for ZPG godville.net

Name: godvilleQT

Version: 0.1

Release: 1

Copyright: GPL

Group: Games

%description

Simple client for Russian ZPG godville.net

written in QT4.

%install

install -s -m 755 -o 0 -g 0 godvilleQT /usr/bin/godvilleQT

install -m 644 -o 0 -g 0 libqprogplug.so /usr/lib/libqprogplug.so

install -m 644 -o 0 -g 0 libqpushplug.so /usr/lib/libqpushplug.so

install -m 644 -o 0 -g 0 godvilleQT.desktop /usr/share/applications/godvilleQT.desktop

install -m 644 -o 0 -g 0 icon.svg /usr/share/pixmaps/godvilleQT.svg

%files

/usr/bin/godvilleQT

/usr/lib/libqprogplug.so

/usr/lib/libqpushplug.so

/usr/share/applications/godvilleQT.desktop

/usr/share/pixmaps/godvilleQT.svg

