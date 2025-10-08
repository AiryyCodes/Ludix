#pragma once

typedef struct
{
    void *handle;
} Shader;

Shader *shader_create(const char *vert_path, const char *frag_path);
void shader_destroy(Shader *shader);

void shader_begin(Shader *shader);
void shader_end();

typedef enum
{
    UNIFORM_FLOAT,
    UNIFORM_VEC2,
    UNIFORM_VEC3,
    UNIFORM_VEC4,
    UNIFORM_INT,
    UNIFORM_IVEC2,
    UNIFORM_IVEC3,
    UNIFORM_IVEC4,
    UNIFORM_MAT3,
    UNIFORM_MAT4
} UniformType;

void shader_set_uniform(const char *name, UniformType type, const void *value);
