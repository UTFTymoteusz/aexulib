#include "aexulib.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stdlib.h"

#define DEFAULT_BLOCK_SIZE 65536

struct block {
    size_t size;
    bool   free;

    struct block* next;
};
typedef struct block block_t;

struct pool {
    size_t size;
    size_t free;

    bool releasable;

    struct block* first_block;
    struct pool* next;
};
typedef struct pool pool_t;

pool_t* first_pool = NULL;

void* calloc(size_t nmeb, size_t size) {
    return malloc(nmeb * size);
}

void debug_enum_mblocks() {
    pool_t* pool = first_pool;
    block_t* block;

    int pool_id = 0;

    while (pool != NULL) {
        printf("block %i:\n", pool_id);
        block = pool->first_block;

        int block_id = 0;
        while (block != NULL) {
            printf("pool %i; s%i - %s\n", block_id++, block->size, block->free ? "free" : "busy");

            block = block->next;
        }

        pool_id++;
        pool = pool->next;
    }
}

pool_t* create_pool(size_t size) {
    pool_t* pool = pgalloc(size);
    pool->size = size - sizeof(pool_t);
    pool->free = pool->size - sizeof(block_t);
    pool->next = NULL;
    pool->releasable = false;

    block_t* block = (block_t*)(((size_t)pool) + sizeof(pool_t));
    block->size = pool->free;
    block->free = true;
    block->next = NULL;

    pool->first_block = block;

    return pool;
}

void* malloc(size_t size) {
    pool_t* pool = first_pool;
    block_t* block = NULL;

    if (pool == NULL) {
        first_pool = create_pool(DEFAULT_BLOCK_SIZE);
        pool = first_pool;
    }
    block = pool->first_block;

    size_t real_size = size + sizeof(block_t);

    while (true) {
        if (block == NULL) {
            if (pool->next == NULL)
                pool->next = create_pool((real_size > DEFAULT_BLOCK_SIZE) ? real_size + DEFAULT_BLOCK_SIZE : DEFAULT_BLOCK_SIZE);

            debug_enum_mblocks();
            pool = pool->next;
            block = pool->first_block;
        }
        if (!block->free) {
            block = block->next;
            continue;
        }

        if (block->size == size) {
            block->free = false;
            pool->free -= size;
            return (void*)(((size_t)block) + sizeof(block_t));
        }
        else if (block->size > real_size + 32) {
            block_t* new_block = (block_t*)((size_t)block + real_size + sizeof(block_t));

            new_block->size = block->size - real_size;
            new_block->free = true;
            new_block->next = block->next;

            block->size = size;
            block->free = false;
            block->next = new_block;

            pool->free -= real_size;

            return (void*)(((size_t)block) + sizeof(block_t));
        }
        block = block->next;
    }
}

void free(void* ptr) {
    block_t* block = ptr - sizeof(block_t);
    block->free = true;
}

void exit(int status) {
    syscall(SYSCALL_EXIT, status);
}