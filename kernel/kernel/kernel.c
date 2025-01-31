#include <stdio.h>
#include <string.h>

#include <kernel/drv/tty.h>
#include <kernel/drv/keyboard.h>
#include <kernel/apps/handle_command.h>

void kernel_main(void) {
	terminal_initialize();
	copyright_text();
	while (1) {
        handle_command(keyboard_input());
    }
}
