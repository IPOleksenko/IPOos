#include <stddef.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void* calloc(size_t num, size_t size) {
    size_t total_size = num * size;  // total memory size to allocate
    void* ptr = malloc(total_size);  // allocate memory using malloc

    if (ptr != NULL) {
        // clear allocated memory with zero bytes
        memset(ptr, 0, total_size);
    }

    return ptr;  // return a pointer to allocated and freed memory
}
