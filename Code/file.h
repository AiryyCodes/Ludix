#pragma once

#include <stdio.h>

typedef struct
{
    FILE *file;

    const char *path;
} File;

void file_open(File *file, const char *path, const char *mode);
char *file_read_all(File *file);
