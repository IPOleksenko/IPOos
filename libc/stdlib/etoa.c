#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
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

void etoa(double value, char* buffer, int precision) {
    if (precision < 0) precision = 6;

    int exp = 0;
    bool negative = false;

    if (value < 0) {
        negative = true;
        value = -value;
    }

    if (value != 0.0) {
        while (value >= 10.0) {
            value /= 10.0;
            exp++;
        }
        while (value < 1.0) {
            value *= 10.0;
            exp--;
        }
    }

    if (negative) {
        *buffer++ = '-';
    }

    ftoa(value, buffer, precision);

    while (*buffer != '\0') buffer++;
    *buffer++ = 'e';

    if (exp < 0) {
        *buffer++ = '-';
        exp = -exp;
    } else {
        *buffer++ = '+';
    }

    intToStr(exp, buffer, 2);
}