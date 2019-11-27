#include "aexulib.h"
#include <stddef.h>

void* pgalloc(size_t bytes) {
    return (void*)syscall(SYSCALL_PGALLOC, bytes);
}

void pgfree(void* page, size_t bytes) {
    syscall(SYSCALL_PGFREE, page, bytes);
}