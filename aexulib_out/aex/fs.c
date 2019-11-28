#include "aexulib.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

#include "fs.h"

bool fexists(char* path) {
    return (bool) syscall(SYSCALL_FEXISTS, path);
}

int finfo(char* path, finfo_t* finfo) {
    return (bool) syscall(SYSCALL_FINFO, path, finfo);
}

void ftranslate(char* buffer, char* base, char* path) {
    if (path[0] == '/' || base == NULL)
        strcpy(buffer, path);
    else {
        if (base[0] != '/')
            sprintf(buffer, "/%s/%s", base, path);
        else
            sprintf(buffer, "%s/%s", base, path);
    }
    char* out  = buffer;

    char specbuff[4];
    uint8_t spb = 0;

    memset(specbuff, '\0', 4);
    
    char* start = out;

    *out = *buffer;
    if (*buffer == '\0')
        return;

    if (*buffer == '/') {
        ++buffer;
        ++out;
    }
    while (true) {
        if (spb < sizeof(specbuff) - 1 && *buffer != '/')
            specbuff[spb++] = *buffer;

        if (*buffer == '/' || *buffer == '\0') {
            if (strcmp(specbuff, "") == 0 && *buffer != '\0')
                out--;
            else if (strcmp(specbuff, "..") == 0) {
                out--;
                while (*out != '/' && out != start)
                    --out;

                if (out != start)
                    --out;

                while (*out != '/' && out != start)
                    --out;

                *out = '/';

                if (*buffer == '\0')
                    ++out;
            }
            else if (strcmp(specbuff, ".") == 0)
                out -= 2;

            memset(specbuff, '\0', 4);
            spb = 0;
        }
        *out = *buffer;

        if (*buffer == '\0')
            break;

        ++buffer;
        ++out;
    }
}