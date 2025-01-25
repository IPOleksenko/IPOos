#include "include/terminal.h"
#include "include/io.h"
#include "include/keyboard.h"

const char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

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

            default: // Regular character
                if (key && buffer_index < sizeof(input_buffer) - 1) {
                    input_buffer[buffer_index++] = key;
                    terminal_putchar(key);
                }
                break;
        }
    }
}
