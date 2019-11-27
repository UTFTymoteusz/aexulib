#pragma once

#include <stddef.h>

#define SYSCALL_SLEEP     0
#define SYSCALL_YIELD     1
#define SYSCALL_EXIT      2
#define SYSCALL_THEXIT    3
#define SYSCALL_FOPEN     4
#define SYSCALL_FREAD     5
#define SYSCALL_FWRITE    6
#define SYSCALL_FCLOSE    7
#define SYSCALL_FSEEK     8
#define SYSCALL_FEXISTS   9
#define SYSCALL_FINFO    17
#define SYSCALL_FCOUNT   18
#define SYSCALL_FLIST    19
#define SYSCALL_PGALLOC  10
#define SYSCALL_PGFREE   11
#define SYSCALL_SPAWN    12
#define SYSCALL_EXEC     13
#define SYSCALL_WAIT     14
#define SYSCALL_GETCWD   15
#define SYSCALL_SETCWD   16

#define SYSCALL_PROCTEST 23

// AEX return codes
enum aex_return_code {
    ERR_GENERAL       = -0x000001,
    ERR_INV_ARGUMENTS = -0x000002,
    ERR_NO_SPACE      = -0x000003,
    ERR_ALREADY_DONE  = -0x000004,
    ERR_NOT_POSSIBLE  = -0x000005,
    ERR_NOT_FOUND     = -0x000006,
    ERR_TOO_MUCH      = -0x00000F,

    DEV_ERR_NOT_FOUND     = -0x0D0006,
    DEV_ERR_NOT_SUPPORTED = -0x0D000C,

    EXE_ERR_INVALID_CPU  = -0x0E0001,
    EXE_ERR_INVALID_FILE = -0x0E0002,

    FS_ERR_NOT_FOUND  = -0x0F0006,
    FS_ERR_NO_MATCHING_FILESYSTEM = -0x0F0007,
    FS_ERR_IS_DIR     = -0x0F0008,
    FS_ERR_READONLY   = -0x0F0009,
    FS_ERR_NOT_DIR    = -0x0F000A,
    FS_ERR_NOT_OPEN   = -0x0F000B,
    FS_ERR_NOT_A_DEV  = -0x0F000D,
    FS_ERR_WRONG_MODE = -0x0F000E,

    ERR_UNKNOWN       = -0xFFFFFF,
};

long syscall(long id, ...);

void* pgalloc(size_t bytes);
void pgfree(void* page, size_t bytes);