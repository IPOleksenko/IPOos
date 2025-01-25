#ifndef IO_H
#define IO_H

#include <stdint.h>

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t value);

#endif // IO_H