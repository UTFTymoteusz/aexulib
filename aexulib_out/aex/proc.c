#include "aexulib.h"

#include "proc.h"

void sleep(long delay) {
    syscall(SYSCALL_SLEEP, delay);
}

void yield() {
    syscall(SYSCALL_YIELD);
}

int spawn(char* image_path, spawn_options_t* options, ...) {    
    return syscall(SYSCALL_SPAWN, image_path, options);
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