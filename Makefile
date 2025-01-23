# Set the names and paths for the files
BOOTLOADER_SRC = boot/bootloader.s
BOOTLOADER_BIN = build/bootloader.bin
DISK_IMG = build/ipoos.img

# Sizes for creating the empty disk image
DISK_SIZE = 2880
SECTOR_SIZE = 512

# Default rule
all: $(DISK_IMG)

# Create the build folder
build/:
	mkdir -p build

# Rule for building the bootloader
$(BOOTLOADER_BIN): build/ $(BOOTLOADER_SRC)
	@echo "Building bootloader..."
	nasm -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)

# Rule for creating an empty disk image and writing the bootloader
$(DISK_IMG): $(BOOTLOADER_BIN)
	@echo "Creating empty disk image..."
	dd if=/dev/zero of=$(DISK_IMG) bs=$(SECTOR_SIZE) count=$(DISK_SIZE)
	@echo "Copying bootloader to the image..."
	dd if=$(BOOTLOADER_BIN) of=$(DISK_IMG) bs=$(SECTOR_SIZE) count=1 conv=notrunc

# Clean up
clean:
	rm -f $(BOOTLOADER_BIN) $(DISK_IMG)
