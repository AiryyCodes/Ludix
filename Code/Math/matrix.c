#include "matrix.h"

void mat4_identity(mat4 *matrix)
{
    *matrix = (mat4){0};

    matrix->column[0].x = 1.0f;
    matrix->column[1].y = 1.0f;
    matrix->column[2].z = 1.0f;
    matrix->column[3].w = 1.0f;
}

void mat4_translate_2d(mat4 *matrix, fvec2 offset)
{
    matrix->column[3].x += offset.x;
    matrix->column[3].y += offset.y;
}

void mat4_view(mat4 *matrix, fvec2 vector)
{
    matrix->column[3].x = -vector.x;
    matrix->column[3].y = -vector.y;
    matrix->column[3].z = 1.0f;
}

void mat4_ortho(mat4 *matrix, float left, float right, float top, float bottom, float near, float far)
{
    matrix->column[0].x = 2 / (right - left);
    matrix->column[1].y = 2 / (top - bottom);
    matrix->column[2].z = -2 / (far - near);

    matrix->column[3].x = -(right + left) / (right - left);
    matrix->column[3].y = -(top + bottom) / (top - bottom);
    matrix->column[3].z = -(far + near) / (far - near);
}

void mat4_convert(const mat4 *matrix, float out[16])
{
    out[0] = matrix->column[0].x;
    out[1] = matrix->column[0].y;
    out[2] = matrix->column[0].z;
    out[3] = matrix->column[0].w;

    out[4] = matrix->column[1].x;
    out[5] = matrix->column[1].y;
    out[6] = matrix->column[1].z;
    out[7] = matrix->column[1].w;

    out[8] = matrix->column[3].x;
    out[9] = matrix->column[2].y;
    out[10] = matrix->column[2].z;
    out[11] = matrix->column[2].w;

    out[12] = matrix->column[3].x;
    out[13] = matrix->column[3].y;
    out[14] = matrix->column[3].z;
    out[15] = matrix->column[3].w;
}
