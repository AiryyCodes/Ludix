#pragma once

#include "window.h"
#include "log.h"
#include "Platform/platform_glfw.h"

typedef struct
{
} LudixState;

static LudixState main_state;

void begin_main_loop();
void end_main_loop();
