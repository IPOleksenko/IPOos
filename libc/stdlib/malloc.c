#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <kernel/sys/ioports.h>
#include <kernel/multiboot.h>
#include <kernel/sys/gdt.h>
#include <kernel/sys/idt.h>
#include <kernel/sys/isr.h>
#include <kernel/sys/paging.h>
#include <kernel/sys/kheap.h>
#include <kernel/sys/pic.h>
#include <kernel/panic.h>
#include <kernel/sys/pit.h>

void* malloc(size_t size) {
    return kmalloc(size);
}
