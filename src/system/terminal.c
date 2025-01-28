#include "include/terminal.h"
#include "include/keyboard.h"
#include "include/ioports.h"

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0;
uint16_t* terminal_buffer = NULL;

void scroll_terminal(void)
{
    // Move each row of the buffer up by one
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t from_index = y * VGA_WIDTH + x;
            const size_t to_index = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[to_index] = terminal_buffer[from_index];
        }
    }

    // Clear the last row of the buffer
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }

    // Adjust the row position to stay within bounds
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_clear(void) 
{
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            terminal_putentryat(' ', terminal_color, x, y);
        }
    }
    terminal_row = 0;
    terminal_column = 0;
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_set_cursor_position(uint16_t position) {
    outb(0x3D4, 0x0F); 
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E); 
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
    switch (c) {
        case '\n': // Newline
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT){
                terminal_row = 0; // Reset to the top if the end of the screen is reached
                scroll_terminal();
                }
            break;
        case '\r': // Carriage return
            terminal_column = 0;
            break;
        case '\t': { // Tab
            size_t tab_size = 4; // Tab size
            size_t next_tab_stop = (terminal_column + tab_size) & ~(tab_size - 1);
            while (terminal_column < next_tab_stop) {
                terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
                if (++terminal_column == VGA_WIDTH) {
                    terminal_column = 0;
                    if (++terminal_row == VGA_HEIGHT){
                        terminal_row = 0;
                        scroll_terminal();
                        }
                }
            }
            break;
        }
        case '\b': // Backspace
            if (terminal_column > 0) {
                --terminal_column;
                terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
            } else if (terminal_row > 0) {
                --terminal_row;
                terminal_column = VGA_WIDTH - 1;
                terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
            }
            break;
        default: // Regular characters
            terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if (++terminal_column == VGA_WIDTH) {
                terminal_column = 0;
                if (++terminal_row == VGA_HEIGHT){
                    terminal_row = 0;
                    scroll_terminal();
                    }
            }
            break;
    }
    // Update the hardware cursor
    terminal_set_cursor_position(terminal_row * VGA_WIDTH + terminal_column);
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void copyright_text()
{
    // Strings to display
    const char* left_text = "IPO_OS.";
    const char* right_text = "Created by IPOleksenko.";
    
    // Calculate padding spaces
    size_t left_text_len = strlen(left_text);
    size_t right_text_len = strlen(right_text);
    size_t padding = VGA_WIDTH - left_text_len - right_text_len;

    // Save the original color to restore later
    uint8_t original_color = terminal_color;

    // Set custom color for header
    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));

    // Write left-aligned text, padding, and right-aligned text in one line
    terminal_writestring(left_text);
    for (size_t i = 0; i < padding; i++) {
        terminal_putchar(' ');
    }
    terminal_writestring(right_text);

    // Restore original color
    terminal_setcolor(original_color);
    terminal_writestring("\n");
}
