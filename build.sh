#!/bin/bash

# ===========================
# Set up environment variables
# ===========================

# Path to cross-compilers
CROSS=~/opt/cross/bin
# Directory where the build output will be stored
BUILD_DIR="build/IPO_OS"

# ============================
# Create necessary build directories
# ============================

echo "Creating build directory..."
mkdir -p $BUILD_DIR || { echo "Failed to create directory"; exit 1; }

# ==============================
# Compile kernel and related files
# ==============================

echo "Compiling all .c files in kernel directory..."
for file in $(find kernel -type f -name "*.c"); do
    obj_file="build/$(basename ${file%.*}).o"
    echo "Compiling $file to $obj_file..."
    $CROSS/i686-elf-gcc -I kernel -c "$file" -o "$obj_file" -std=gnu99 -ffreestanding -O2 -Wall -Wextra || { echo "Compilation of $file failed"; exit 1; }
done

echo "Compiling bootloader..."
$CROSS/i686-elf-as boot/bootloader.s -o build/bootloader.o || { echo "Bootloader compilation failed"; exit 1; }

# ========================
# Link the final binary
# ========================

echo "Linking all object files in build directory..."
obj_files=$(find build -type f -name "*.o")
$CROSS/i686-elf-gcc -T linker/linker.ld -o $BUILD_DIR/IPO_OS.bin -ffreestanding -O2 -nostdlib $obj_files -lgcc || { echo "Linking failed"; exit 1; }

# ============================
# Successful build completion
# ============================

echo "Build completed successfully!"
echo "Final binary: $BUILD_DIR/IPO_OS.bin"
