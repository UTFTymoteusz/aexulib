#include <stdint.h>

#include "aexulib.h"

uint64_t get_sysvar(int id) {
    return syscall(SYSCALL_SYSVAR, id);
}