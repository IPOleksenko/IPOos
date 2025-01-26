#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

extern const char keymap[128];
void set_cursor_position(uint16_t position);
char* keyboard_input();

#endif // KEYBOARD_H