# ===============================
#         Build Parameters       
# ===============================

BUILD_DIR := build
DISK_DIR  := $(BUILD_DIR)/disk
DISK_IMAGE := $(DISK_DIR)/disk.img
KERNEL_BIN := $(BUILD_DIR)/IPO_OS/IPO_OS.bin

# ===============================
#          Main Targets         
# ===============================
.PHONY: all clean build disk run

all: clean build disk run

# ===============================
#         Clean Build            
# ===============================
clean:
	@echo "🔄 Cleaning build..."
	rm -rf $(BUILD_DIR)

# ===============================
#          Build Project         
# ===============================
build:
	@echo "⚙️  Starting build via build.sh..."
	@./tools/build.sh

# ===============================
#      Create Disk Image         
# ===============================
disk:
	@echo "💾 Creating disk image..."
	@mkdir -p $(DISK_DIR)
	@dd if=/dev/zero of=$(DISK_IMAGE) bs=512 count=2880

# ===============================
#         Run in QEMU            
# ===============================
run:
	@echo "🚀 Running in QEMU..."
	@if [ ! -f "$(DISK_IMAGE)" ]; then \
		qemu-system-i386 -kernel build/IPO_OS/IPO_OS.bin -d int; \
	else \
		qemu-system-i386 -kernel build/IPO_OS/IPO_OS.bin -drive file=$(DISK_IMAGE),format=raw -d int; \
	fi

.PHONY: all clean build disk run
