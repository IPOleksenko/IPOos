#include <stdint.h>
#include <stdio.h>

static uint32_t seed = 1; // Initial value for the random number generator

int rand(void) {
    // Linear Constant High Summary Generator (LCG)
    // Parameters for simple LCG: 
    //   X (n + 1) = (a *x (n) + c) % m
    // where a = 1103515245, C = 12345, M = 2^31
    // You can use other parameters depending on your requirements

    const uint32_t a = 1103515245;
    const uint32_t c = 12345;
    const uint32_t m = 1U << 31; // 2^31

    seed = (a * seed + c) % m;
    return (int)(seed / 65536) % 32768; // Bringing to the range [0, 32767]
}