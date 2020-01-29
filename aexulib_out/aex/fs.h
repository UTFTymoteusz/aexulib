#pragma once

#include "stdio.h"

#include <stdbool.h>
#include <stdint.h>

enum fs_type {
    FS_TYPE_FILE  = 2,
    FS_TYPE_DIR   = 3,
    FS_TYPE_CDEV  = 4,
    FS_TYPE_BDEV  = 5,
};

struct dentry {
    char name[256];
    uint8_t type;
};
typedef struct dentry dentry_t;

struct dir {
    int count;
    int pos;

    dentry_t* dentries;
};
typedef struct dir DIR;

struct finfo {
    uint64_t inode;
    uint8_t  type;
};
typedef struct finfo finfo_t;

struct ttysize {
    uint16_t rows;
    uint16_t columns;
    uint16_t pixel_height;
    uint16_t pixel_width;
};

bool fexists(char* path);
int finfo(char* path, finfo_t*);

void ftranslate(char* buffer, char* base, char* path);

DIR* opendir(char* path);
dentry_t* readdir(DIR*);
void closedir(DIR*);

#include "vals/ioctl_names.h"
long ioctl(FILE* file, long code, void* mem);