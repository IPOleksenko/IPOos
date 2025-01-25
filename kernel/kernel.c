#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "Must be compiled using the ix86-elf compiler."
#endif

#include "include/vga.h"
#include "include/string.h"
#include "include/terminal.h"

void kernel_main(void) 
{
    terminal_initialize();
    copyright_text();

    // test text
    terminal_writestring("Hello, World!\n");
    terminal_writestring("Hello, World!\n");
    terminal_writestring("Hello, World!\n");
    terminal_writestring("Hello, World!\n");
}

