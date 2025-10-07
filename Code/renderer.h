#pragma once

#include "Renderer/shader.h"
#include "types.h"

typedef struct
{
    Shader *active_shader;
} RendererState;

static RendererState renderer_state;

void clear(int flags);
void clear_color(Color color);

void viewport_set(int width, int height);
