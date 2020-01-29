#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define EOF (-1)

// implement perror pls

struct file {
    // temporary, i cant malloc() yet
};
typedef struct file FILE;

FILE* _stdin, * _stdout, * _stderr;

#define stdin  _stdin
#define stdout _stdout
#define stderr _stderr

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