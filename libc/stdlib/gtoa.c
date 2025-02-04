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

void gtoa(double value, char *buffer, int precision) {
    char f_buffer[64];
    char e_buffer[64];

    ftoa(value, f_buffer, precision);
    etoa(value, e_buffer, precision);

    if (strlen(f_buffer) <= strlen(e_buffer)) {
        strcpy(buffer, f_buffer);
    } else {
        strcpy(buffer, e_buffer);
    }
}