#include "aexulib.h"

#include "stdlib.h"
#include <stdbool.h>

#include "fs.h"

bool fexists(char* path) {
    return (bool) syscall(SYSCALL_FEXISTS, path);
}

int finfo(char* path, finfo_t* finfo) {
    return (bool) syscall(SYSCALL_FINFO, path, finfo);
}