#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define EOF (-1)

struct file {
    // temporary, i cant malloc() yet
};
typedef struct file FILE;

#define stdin  (FILE*)0
#define stdout (FILE*)1
#define stderr (FILE*)2

FILE* fopen(const char* filename, const char* mode);
size_t fread(const void* ptr, size_t size, size_t nitems, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream);
int fclose(FILE* stream);
int fseek(FILE* stream, long offset, int mode);

int vfprintf(FILE* stream, const char* restrict format, va_list parameters);
int printf(const char* restrict format, ...);
int fprintf(FILE* stream, const char* restrict format, ...);
int sprintf(char* dst, const char* restrict format, ...);

int getchar();
int getc(FILE* stream);
int putchar(int c);
int putc(int c, FILE* stream);