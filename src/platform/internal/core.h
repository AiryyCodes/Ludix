#pragma once

#include <stdbool.h>

typedef struct
{
    struct
    {
        const char *title;
        int width;
        int height;
        bool ready;
    } window;
} CoreState;

extern CoreState core;
