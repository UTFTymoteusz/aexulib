#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static bool print(const char* data, size_t length, FILE* stream) {
    const uint8_t* bytes = (const uint8_t*)data;

    fwrite(data, length, length, stream);
    return true;
}

int vfprintf(FILE* stream, const char* restrict format, va_list parameters) {
    char itoa_buffer[128];
    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;

            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;

            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount, stream))
                return -1;

            format += amount;
            written += amount;

            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);

            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c), stream))
                return -1;

            written++;
        }
        else if (*format == 'x') {
            format++;
            uint64_t val = (uint64_t) va_arg(parameters, uint64_t);

            itoa(val, itoa_buffer, 16);

            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(itoa_buffer, strlen(itoa_buffer), stream))
                return -1;

            written++;
        }
        else if (*format == 'i') {
            format++;
            uint64_t val = (uint64_t) va_arg(parameters, uint64_t);

            itoa(val, itoa_buffer, 10);

            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(itoa_buffer, strlen(itoa_buffer), stream))
                return -1;

            written++;
        }
        else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len, stream))
                return -1;

            written += len;
        }
        else {
            format = format_begun_at;
            size_t len = strlen(format);

            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len, stream))
                return -1;

            written += len;
            format += len;
        }
    }
    va_end(parameters);
    return written;
}