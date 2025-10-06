#pragma once

#include "Renderer/shader.h"
#include "types.h"

typedef struct
{
    Shader *active_shader;
} RendererState;

static RendererState renderer_state;

void clear_color(Color color);

void shader_begin(Shader *shader);
void shader_end();
