#include "aexulib.h"
#include "stdlib.h"

#include "fs.h"

DIR* opendir(char* path) {
    DIR* dir = malloc(sizeof(DIR));
    dir->count = syscall(SYSCALL_FCOUNT, path);
    if (dir->count < 0)
        return NULL;

    dir->pos = 0;
    dir->dentries = calloc(dir->count, sizeof(dentry_t));
    
    syscall(SYSCALL_FLIST, path, dir->dentries, dir->count);
    return dir;
}

dentry_t* readdir(DIR* dir) {
    if (dir->pos >= dir->count)
        return NULL;

    return &(dir->dentries[dir->pos++]);
}

void closedir(DIR* dir) {
    free(dir->dentries);
    free(dir);
}