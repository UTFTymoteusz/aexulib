#pragma once

#include <stddef.h>

struct spawn_options {
    int stdin;
    int stdout;
    int stderr;
};
typedef struct spawn_options spawn_options_t;

void sleep(long delay);
void yield();

int spawna(char* image_path, spawn_options_t* options, int arg_count, char* args[]);
int spawn (char* image_path, spawn_options_t* options, int arg_count, ...);
int wait(int pid);

int getcwd(char* buffer, size_t len);
int setcwd(char* path);