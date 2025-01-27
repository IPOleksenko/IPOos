#include <stdbool.h>
#include <stdint.h>
#include "include/keyboard.h"
#include "include/terminal.h"
#include "include/io.h"
#include "include/keymap.h"

char* keyboard_input() {
    static char input_buffer[256];
    size_t buffer_index = 0;
    bool shift_pressed = false;

    terminal_writestring("\n> ");
    while (1) {
        // Wait until the keyboard controller is ready
        if (!(inb(0x64) & 0x1)) {
            continue;
        }

        uint8_t scancode = inb(0x60); // Read the scancode

        // Check for key release (break code)
        if (scancode & 0x80) {
            uint8_t key_released = scancode & 0x7F; // Get the make code
            if (key_released == 0x2A || key_released == 0x36) { // Left or Right Shift released
                shift_pressed = false;
            }
            continue;
        }

        // Check for key press
        if (scancode == 0x2A || scancode == 0x36) { // Left or Right Shift pressed
            shift_pressed = true;
            continue;
        }

        const char* current_keymap = get_keymap(shift_pressed);
        char key = current_keymap[scancode];

        switch (key) {
            case '\n': // Enter
                if (buffer_index > 0) {
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
