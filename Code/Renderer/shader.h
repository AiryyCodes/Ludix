#pragma once

typedef struct
{
    void *handle;
} Shader;

Shader *shader_create(const char *vert_path, const char *frag_path);
void shader_destroy(Shader *shader);

void shader_begin(Shader *shader);
void shader_end();
