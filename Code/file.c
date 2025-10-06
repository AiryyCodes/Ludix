#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void file_open(File *file, const char *path, const char *mode)
{
    FILE *base_file = fopen(path, mode);
    if (!base_file)
    {
        printf("Failed to open file '%s'\n", path);
        return;
    }

    file->file = base_file;
    file->path = path;
}

char *file_read_all(File *file)
{
    struct stat statbuf;
    int status = stat(file->path, &statbuf);
    if (status == -1)
    {
        return "";
    }

    int fileSize = statbuf.st_size;
    char *content = malloc(fileSize);

    int index = 0;
    char c;
    while ((c = fgetc(file->file)) != EOF)
    {
        content[index++] = c;
    }

    content[index] = '\0';

    return content;
}
