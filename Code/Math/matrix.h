#pragma once

#include "vector.h"

typedef struct
{
    fvec4 column[4];
} mat4;

void mat4_identity(mat4 *matrix);
void mat4_translate_2d(mat4 *matrix, fvec2 offset);

void mat4_view(mat4 *matrix, fvec2 vector);
void mat4_ortho(mat4 *matrix, float left, float right, float top, float bottom, float near, float far);

void mat4_convert(const mat4 *matrix, float out[16]);
