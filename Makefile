# Default main target
all: clean build run

# Remove compiled files
clean:
	rm -rf build

# Build the project using build.sh
build:
	@echo "Starting build through build.sh..."
	@./build.sh

# Run in QEMU
run:
	qemu-system-i386 -kernel build/IPO_OS/IPO_OS.bin

.PHONY: all clean build run
