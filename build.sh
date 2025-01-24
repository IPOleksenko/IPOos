#!/bin/bash

# ===========================
# Set up environment variables
# ===========================

# Path to cross-compilers
CROSS=~/opt/cross/bin
# Directory where the build output will be stored
BUILD_DIR="build/IPO_OS"

# ===========================
# Print paths to the compilers
# ===========================

echo "Path to i686-elf-gcc: $CROSS/i686-elf-gcc"
echo "Path to i686-elf-as: $CROSS/i686-elf-as"

# ============================
# Create necessary build directories
# ============================

echo "Creating build directory..."
mkdir -p $BUILD_DIR || { echo "Failed to create directory"; exit 1; }

# ==============================
# Compile kernel and bootloader
# ==============================

echo "Compiling kernel..."
$CROSS/i686-elf-gcc -c kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra || { echo "Kernel compilation failed"; exit 1; }

echo "Compiling bootloader..."
$CROSS/i686-elf-as boot/bootloader.s -o build/bootloader.o || { echo "Bootloader compilation failed"; exit 1; }

# ========================
# Link the final binary
# ========================

echo "Linking final binary..."
$CROSS/i686-elf-gcc -T linker/linker.ld -o $BUILD_DIR/IPO_OS.bin -ffreestanding -O2 -nostdlib build/bootloader.o build/kernel.o -lgcc || { echo "Linking failed"; exit 1; }

# ============================
# Successful build completion
# ============================

echo "Build completed successfully!"
echo "Final binary: $BUILD_DIR/IPO_OS.bin"
