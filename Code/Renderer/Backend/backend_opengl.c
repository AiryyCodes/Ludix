#include "Renderer/mesh.h"
#include "Renderer/shader.h"
#include "file.h"
#include "log.h"
#include "renderer.h"
#include "types.h"

#include <stdint.h>
#include <stdlib.h>
#include <glad/gl.h>

void clear(int flags)
{
    glClear(flags);
}

void clear_color(Color color)
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}

void viewport_set(int width, int height)
{
    glViewport(0, 0, width, height);
}

Mesh *mesh_create(const Vertex vertices[], u32 num_vertices)
{
    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->num_vertices = num_vertices;

    u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    mesh->handle = (void *)(uintptr_t)vao;

    u32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    mesh->vertex_buffer = (void *)(uintptr_t)vbo;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    return mesh;
}

void mesh_destroy(Mesh *mesh)
{
    if (mesh == NULL)
        return;

    glDeleteBuffers(GL_ARRAY_BUFFER, (u32 *)(uintptr_t *)&mesh->vertex_buffer);
    glDeleteVertexArrays(1, (u32 *)(uintptr_t *)&mesh->handle);

    free(mesh);
}

void mesh_draw(const Mesh *mesh)
{
    glBindVertexArray((u32)(uintptr_t)mesh->handle);
    glDrawArrays(GL_TRIANGLES, 0, mesh->num_vertices);
}

u32 shader_compile(const char *path, const char *name, u32 type)
{
    u32 id = glCreateShader(type);

    File file;
    file_open(&file, path, "r");

    const char *source = file_read_all(&file);
    glShaderSource(id, 1, &source, NULL);

    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char log[512];
        glGetShaderInfoLog(id, 512, NULL, log);

        LOG("Failed to compile %s shader\n%s\n", name, log);

        exit(EXIT_FAILURE);
    }

    return id;
}

Shader *shader_create(const char *vert_path, const char *frag_path)
{
    Shader *shader = malloc(sizeof(Shader));

    u32 vertex_id = shader_compile(vert_path, "vertex", GL_VERTEX_SHADER);
    u32 fragment_id = shader_compile(frag_path, "fragment", GL_FRAGMENT_SHADER);

    u32 program = glCreateProgram();
    shader->handle = (void *)(uintptr_t)program;

    glAttachShader(program, vertex_id);
    glAttachShader(program, fragment_id);

    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);

        printf("Failed to link shader program\n%s\n", log);

        exit(EXIT_FAILURE);

        return NULL;
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return shader;
}

void shader_destroy(Shader *shader)
{
    if (shader == NULL)
        return;

    glDeleteProgram((u32)(uintptr_t)shader->handle);

    free(shader);
}

void shader_begin(Shader *shader)
{
    if (shader == NULL)
        return;

    glUseProgram((u32)(uintptr_t)shader->handle);

    renderer_state.active_shader = shader;
}

void shader_end()
{
    glUseProgram(0);
    renderer_state.active_shader = NULL;
}

void shader_set_uniform(const char *name, UniformType type, const void *value)
{
    int loc = glGetUniformLocation((u32)(uintptr_t)renderer_state.active_shader->handle, name);
    if (loc == -1)
    {
        LOG("Warning: uniform '%s' not found.\n", name);
        return;
    }

    switch (type)
    {
    case UNIFORM_FLOAT:
        glUniform1f(loc, *(float *)value);
        break;
    case UNIFORM_VEC2:
        glUniform2fv(loc, 1, (const float *)value);
        break;
    case UNIFORM_VEC3:
        glUniform3fv(loc, 1, (const float *)value);
        break;
    case UNIFORM_VEC4:
        glUniform4fv(loc, 1, (const float *)value);
        break;
    case UNIFORM_INT:
        glUniform1i(loc, *(int *)value);
        break;
    case UNIFORM_IVEC2:
        glUniform2iv(loc, 1, (const int *)value);
        break;
    case UNIFORM_IVEC3:
        glUniform3iv(loc, 1, (const int *)value);
        break;
    case UNIFORM_IVEC4:
        glUniform4iv(loc, 1, (const int *)value);
        break;
    case UNIFORM_MAT3:
        glUniformMatrix3fv(loc, 1, GL_FALSE, (const float *)value);
        break;
    case UNIFORM_MAT4:
        glUniformMatrix4fv(loc, 1, GL_FALSE, (const float *)value);
        break;
    default:
        LOG("Error: Unknown uniform type for '%s'\n", name);
        break;
    }
}
