#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int printf(const char* restrict format, ...) {
    va_list args;
    va_start(args, format);

    int ret = vfprintf(stdout, format, args);

    va_end(args);
    return ret;
}