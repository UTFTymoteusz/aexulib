#include <stdarg.h>

#include "aexulib.h"

#include "proc.h"

void sleep(long delay) {
    syscall(SYSCALL_SLEEP, delay);
}

void yield() {
    syscall(SYSCALL_YIELD);
}

int spawna(char* image_path, spawn_options_t* options, int arg_count, char* args[]) {
    char* argsn[arg_count + 1];

    for (int i = 0; i < arg_count; i++)
        argsn[i] = args[i];

    argsn[arg_count] = NULL;

    return syscall(SYSCALL_SPAWN, image_path, options, argsn);
}

int spawn(char* image_path, spawn_options_t* options, int arg_count, ...) {
    char* args[arg_count];
    
    va_list argsl;
    va_start(argsl, arg_count);

    for (int i = 0; i < arg_count; i++)
        args[i] = va_arg(argsl, char*);

    va_end(argsl);
    
    return spawna(image_path, options, arg_count, args);
}

int wait(int pid) {    
    return syscall(SYSCALL_WAIT, pid);
}

int getcwd(char* buffer, size_t len) {
    return syscall(SYSCALL_GETCWD, buffer, len);
}

int setcwd(char* path) {
    return syscall(SYSCALL_SETCWD, path);
}