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
#include <kernel/sys/pic.h>
#include <kernel/panic.h>
#include <kernel/sys/pit.h>
#include <kernel/sys/kheap.h>

// Function my_realloc
void* realloc(void* ptr, size_t new_size) {
    header_t* header = (header_t*)((char*)ptr - sizeof(header_t));
    size_t old_size = header->size;

    // If the new size is 0, the function behavior should be similar to free
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    // If the pointer is NULL, the function behavior should be similar to malloc
    if (ptr == NULL) {
        return malloc(new_size);
    }

    // Allocating a new memory region
    void* new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        // If memory allocation fails, return NULL
        return NULL;
    }

    // Copying data from the old memory region to the new one
    memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);

    // Freeing the old memory region
    free(ptr);

    return new_ptr;
}
