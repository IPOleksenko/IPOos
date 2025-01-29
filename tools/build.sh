#!/bin/bash

# ===========================
# 🌍 Set up environment variables
# ===========================

# 🔧 Path to cross-compilers
CROSS=~/opt/cross/bin
# 📂 Directory where the build output will be stored
BUILD_DIR="build"
# 📚 Paths to newlib
NEWLIB_INCLUDE="libs/newlib/i686-elf/include"
NEWLIB_LIB="libs/newlib/i686-elf/lib"

# ============================
# 📂 Create necessary build directories
# ============================

echo "📁 Creating build directory..."
mkdir -p $BUILD_DIR/IPO_OS || { echo "❌ Failed to create directory"; exit 1; }

# ==============================
# ⚙️ Compile kernel.c
# ==============================

echo "🛠️ Compiling kernel.c..."
KERNEL_SRC="kernel/kernel.c"
KERNEL_OBJ="$BUILD_DIR/kernel.o"

if [ -f "$KERNEL_SRC" ]; then
    $CROSS/i686-elf-gcc -I kernel -I src -I "$NEWLIB_INCLUDE" \
        -c "$KERNEL_SRC" -o "$KERNEL_OBJ" -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
        || { echo "❌ Compilation of kernel.c failed"; exit 1; }
else
    echo "❌ Error: $KERNEL_SRC not found"
    exit 1
fi

# ==============================
# 📝 Compile other .c files
# ==============================

echo "🛠️ Compiling all .c files in src directory..."
for file in $(find src -type f -name "*.c"); do
    obj_file="$BUILD_DIR/$(basename ${file%.*}).o"
    echo "🔄 Compiling $file to $obj_file..."
    $CROSS/i686-elf-gcc -I src -I "$NEWLIB_INCLUDE" \
        -c "$file" -o "$obj_file" -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
        || { echo "❌ Compilation of $file failed"; exit 1; }
done

# ========================
# 🏁 Compile bootloader
# ========================

echo "🛠️ Compiling bootloader..."
BOOTLOADER_SRC="boot/bootloader.s"
BOOTLOADER_OBJ="$BUILD_DIR/bootloader.o"

if [ -f "$BOOTLOADER_SRC" ]; then
    $CROSS/i686-elf-as "$BOOTLOADER_SRC" -o "$BOOTLOADER_OBJ" || { echo "❌ Bootloader compilation failed"; exit 1; }
else
    echo "❌ Error: $BOOTLOADER_SRC not found"
    exit 1
fi

# ========================
# 🔗 Link the final binary
# ========================

echo "🔗 Linking all object files in build directory..."
LINKER_SRC="linker/linker.ld"

if [ -f "$LINKER_SRC" ]; then
    obj_files=$(find build -type f -name "*.o")
    $CROSS/i686-elf-gcc -T "$LINKER_SRC" -o "$BUILD_DIR/IPO_OS/IPO_OS.bin" \
        -ffreestanding -O2 -nostdlib -L"$NEWLIB_LIB" $obj_files -lc -lgcc \
        || { echo "❌ Linking failed"; exit 1; }
else
    echo "❌ Error: $LINKER_SRC not found"
    exit 1
fi

# ============================
# 🎉 Successful build completion
# ============================

echo "✅ Build completed successfully!"
echo "🚀 Final binary: $BUILD_DIR/IPO_OS/IPO_OS.bin"
