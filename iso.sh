#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/IPO_OS.kernel isodir/boot/IPO_OS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "IPO_OS" {
	multiboot /boot/IPO_OS.kernel
}
EOF
grub-mkrescue -o IPO_OS.iso isodir
