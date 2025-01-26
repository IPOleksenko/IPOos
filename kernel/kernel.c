#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "Must be compiled using the ix86-elf compiler."
#endif

#include "include/terminal.h"
#include "include/keyboard.h"

#include "include/main.h"

void kernel_main(void) 
{
    terminal_initialize();
    copyright_text();

    main();
}


