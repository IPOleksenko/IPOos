#ifndef IOPORTS_H
#define IOPORTS_H

#include <stdint.h>

// Read a byte from the specified port
uint8_t inb(uint16_t port);

// Read a word (2 bytes) from the specified port
uint16_t inw(uint16_t port);

// Write a byte to the specified port
void outb(uint16_t port, uint8_t value);

// Write a word (2 bytes) to the specified port
void outw(uint16_t port, uint16_t value);

#endif
