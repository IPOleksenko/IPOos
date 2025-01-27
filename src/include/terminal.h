#ifndef TERMINAL_H
#define TERMINAL_H

#include "include/vga.h"
#include "include/string.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;


void scroll_terminal(void);

void terminal_initialize(void);

void terminal_clear(void);

void terminal_setcolor(uint8_t color);

void terminal_set_cursor_position(uint16_t position);

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);

void terminal_write(const char* data, size_t size);

void terminal_writestring(const char* data);

void copyright_text();

#endif