#include <string.h>
#include <stdlib.h>

void dtoa(double num, char* buffer, size_t precision) {
    long long integerPart = (long long)num;
    double fractionalPart = num - integerPart;

    // Convert the integer part of a number to a string
    itoa(integerPart, buffer, 10);

    // Adding a decimal point
    strcat(buffer, ".");

    // Converting the fractional part of a number into a string
    for (size_t i = 0; i < precision; i++) {
        fractionalPart *= 10;
        long long digit = (long long)fractionalPart;
        char digitChar = '0' + digit;
        strcat(buffer, &digitChar);
        fractionalPart -= digit;
    }
}