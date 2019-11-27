#pragma once

#include <stddef.h>

void* calloc(size_t nmeb, size_t size);
void* malloc(size_t size);
void  free(void* ptr);
// implement realloc

void exit(int status);