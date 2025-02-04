#include <stdint.h>
#include <stdio.h>

static uint32_t seed = 1; // Initial value for the random number generator

// The function for installing the initial value of the random number generator
void srand(unsigned int new_seed) {
    seed = new_seed;
}