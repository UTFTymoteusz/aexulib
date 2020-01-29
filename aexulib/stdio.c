#include "aexulib.h"

#include "stdio.h"

FILE* _stdin  = (FILE*)0;
FILE* _stdout = (FILE*)1;
FILE* _stderr = (FILE*)2;

FILE* fopen(const char* filename, const char* mode) {
    long ret = syscall(SYSCALL_FOPEN, filename);
    if (ret < 0) {
        // set errno
        return NULL;
    } 
    return (FILE*)ret;
}

size_t fread(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYSCALL_FREAD, (long)stream, (uint8_t*)ptr, nitems);
}

size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYSCALL_FWRITE, (long)stream, (uint8_t*)ptr, nitems);
}

int fclose(FILE* stream) {
    return syscall(SYSCALL_FCLOSE, (long)stream);
}

int fseek(FILE* stream, long offset, int mode) {
    switch (mode) {
        case 0:
            return syscall(SYSCALL_FSEEK, (long)stream, offset);
        case 1:
        case 2:
            // unimplemented
            break;
    }
}

int getchar() {
    char c;
    fread(&c, 1, 1, stdin);
    return c;
}

int getc(FILE* stream) {
    char c;
    fread(&c, 1, 1, stream);
    return c;
}

int putchar(int c) {
    fwrite(&c, 1, 1, stdout);
}

int putc(int c, FILE* stream) {
    fwrite(&c, 1, 1, stream);
}