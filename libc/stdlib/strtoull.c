#include <stddef.h> // For defining NULL
#include <ctype.h>  // For isdigit and isspace

unsigned long long strtoull(const char* str, char** endptr, int base) {
    const char* s = str;
    unsigned long long result = 0;
    unsigned long long prev_result = 0;

    // Skip leading whitespace characters
    while (isspace(*s)) {
        s++;
    }

    // Process possible sign of the number
    if (*s == '+') {
        s++;
    } else if (*s == '-') {
        s++;  // Negative numbers are ignored for unsigned long long
    }

    // Determine the base (number system)
    if (base == 0) {
        if (*s == '0') {
            if (*(s + 1) == 'x' || *(s + 1) == 'X') {
                base = 16;
                s += 2;
            } else {
                base = 8;
                s++;
            }
        } else {
            base = 10;
        }
    } else if (base == 16) {
        if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X')) {
            s += 2;
        }
    }

    // Main loop for converting the string to a number
    while (*s) {
        int digit = 0;

        if (isdigit(*s)) {
            digit = *s - '0';
        } else if (*s >= 'a' && *s <= 'f') {
            digit = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'F') {
            digit = *s - 'A' + 10;
        } else {
            break;  // Not a valid character for the given number system
        }

        if (digit >= base) {
            break;  // Character exceeds the valid value for this base
        }

        prev_result = result;
        result = result * base + digit;

        // Check for overflow
        if (result < prev_result) {
            result = -1;  // Set the maximum value on overflow
            break;
        }

        s++;
    }

    // Set endptr to the character that stopped the parsing
    if (endptr) {
        *endptr = (char*)s;
    }

    return result;
}
