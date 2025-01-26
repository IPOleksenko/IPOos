#include <stdint.h>

#include "include/keyboard.h"
#include "include/terminal.h"
#include "include/io.h"
#include "include/keymap.h"

void set_cursor_position(uint16_t position) {
    outb(0x3D4, 0x0F); 
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E); 
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

char* keyboard_input() {
    static char input_buffer[256];
    size_t buffer_index = 0;

    terminal_writestring("\n> ");
    while (1) {        
        // Wait until the keyboard controller is ready
        if (!(inb(0x64) & 0x1)) {
            continue;
        }

        uint8_t scancode = inb(0x60); // Read the scancode

        // Ignore break codes (scancode >= 0x80)
        if (scancode & 0x80) {
            continue;
        }

        char key = keymap[scancode];

        switch (key) {
            case '\n': // Enter
                if (buffer_index > 0){
                    input_buffer[buffer_index] = '\0';
                    terminal_putchar('\n');
                    return input_buffer;
                    }
                break;

            case '\b': // Backspace
                if (buffer_index > 0) {
                    buffer_index--;
                    terminal_putchar('\b');
                    terminal_putchar(' ');
                    terminal_putchar('\b');
                }
                break;

            case '\t':  // Tab
                if (buffer_index < sizeof(input_buffer) - 1) {
                    size_t tab_size = 4; // Tab size
                    size_t next_tab_stop = (buffer_index + tab_size) & ~(tab_size - 1);
                    size_t spaces_to_add = next_tab_stop - buffer_index;

                    // Fill the buffer with spaces for the tab
                    for (size_t i = 0; i < spaces_to_add; i++) {
                        if (buffer_index < sizeof(input_buffer) - 1) {
                            input_buffer[buffer_index++] = ' ';
                        }
                        terminal_putchar(' '); // Show space on the screen
                    }
                }
                break;
        

            default: // Regular character
                if (key && buffer_index < sizeof(input_buffer) - 1) {
                    input_buffer[buffer_index++] = key;
                    terminal_putchar(key);
                }
                break;
        }
    }
}
