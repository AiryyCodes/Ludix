#pragma once

#include "ecs_types.h"
#include "window.h"
#include "log.h"
#include "Platform/platform_glfw.h"

typedef struct
{
    ECSWorld *world;

    struct
    {
        float delta;
        float last;
    } time;
} LudixState;

void ludix_init();

void begin_main_loop();
void end_main_loop();

float get_delta_time();
