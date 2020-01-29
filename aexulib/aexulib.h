#pragma once

#include <stddef.h>
#include <stdint.h>

#include "vals/rcode_names.h"
#include "vals/syscall_names.h"
#include "vals/sysvar_names.h"

long syscall(long id, ...);

void* pgalloc(size_t bytes);
void pgfree(void* page, size_t bytes);

uint64_t get_sysvar(int id);