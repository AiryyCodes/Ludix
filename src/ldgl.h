#pragma once

#include "ludix.h"
#include <stdbool.h>
#include <stdlib.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#ifndef LDGL_DEFAULT_BATCH_BUFFER_ELEMENTS
#define LDGL_DEFAULT_BATCH_BUFFER_ELEMENTS 1024
#endif

#ifndef LDGL_DEFAULT_BATCH_DRAWCALLS
#define LDGL_DEFAULT_BATCH_DRAWCALLS 256
#endif

typedef struct
{
    int vertexCount;
    int vertexAlignment;
} LDDrawCall;

typedef struct
{
    int elementCount;

    float *vertices;

    LDDrawCall *drawCalls;
    int drawCounter;

    unsigned int vao;
    unsigned int vbo;
} LDRenderBatch;

typedef struct
{
    LDRenderBatch *currentBatch;
    LDRenderBatch defaultBatch;

    unsigned int defaultShaderId;

    int currentVertices;
} LDGLState;

static LDGLState ldgl = {0};

void ldglInit();

LDRenderBatch ldCreateRenderBatch(int maxElements);
void ldDrawRenderBatch(LDRenderBatch *batch);
void ldDrawActiveRenderBatch();
bool ldCheckRenderBatchLimit(int vertCount);

void ldCreateDefaultShader();
unsigned int ldCompileShader(const char *src, unsigned int type);

void ldBegin();

void ldVertex2f(float x, float y);

// LDGL Implementation

#define LDGL_IMPLEMENTATION

#if defined(LDGL_IMPLEMENTATION)
void ldglInit()
{
    ldgl.defaultBatch = ldCreateRenderBatch(LDGL_DEFAULT_BATCH_BUFFER_ELEMENTS);
    ldgl.currentBatch = &ldgl.defaultBatch;

    ldCreateDefaultShader();
}

LDRenderBatch ldCreateRenderBatch(int maxElements)
{
    LDRenderBatch batch = {0};

    batch.elementCount = maxElements;

    batch.vertices = (float *)calloc(maxElements * 3, sizeof(float));

    batch.drawCalls = (LDDrawCall *)calloc(LDGL_DEFAULT_BATCH_DRAWCALLS, sizeof(LDDrawCall));

    for (int i = 0; i < LDGL_DEFAULT_BATCH_DRAWCALLS; i++)
    {
        batch.drawCalls[i].vertexCount = 0;
        batch.drawCalls[i].vertexAlignment = 0;
    }

    glGenVertexArrays(1, &batch.vao);
    glBindVertexArray(batch.vao);

    glGenBuffers(1, &batch.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
    glBufferData(GL_ARRAY_BUFFER, maxElements * 3 * sizeof(float), batch.vertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    batch.drawCounter = 1;

    return batch;
}

void ldDrawRenderBatch(LDRenderBatch *batch)
{
    if (ldgl.currentVertices > 0)
    {
        glBindVertexArray(batch->vao);

        glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, ldgl.currentVertices * 3 * sizeof(float), batch->vertices);

        for (int i = 0, vertexOffset = 0; i < batch->drawCounter; i++)
        {
            glUseProgram(ldgl.defaultShaderId);

            glDrawArrays(GL_TRIANGLES, vertexOffset, batch->drawCalls[i].vertexCount);

            vertexOffset += batch->drawCalls[i].vertexCount;
        }
    }

    ldgl.currentVertices = 0;

    for (int i = 0; i < LDGL_DEFAULT_BATCH_DRAWCALLS; i++)
    {
        batch->drawCalls[i].vertexCount = 0;
    }

    batch->drawCounter = 1;
}

void ldDrawActiveRenderBatch()
{
    ldDrawRenderBatch(ldgl.currentBatch);
}

bool ldCheckRenderBatchLimit(int vertCount)
{
    bool overflow = false;

    if (ldgl.currentVertices + vertCount >= ldgl.currentBatch->elementCount)
    {
        overflow = true;

        ldDrawRenderBatch(ldgl.currentBatch);
    }

    return overflow;
}

void ldCreateDefaultShader()
{
    const char *vertexSource =
        "#version 430 core\n"

        "layout(location = 0) in vec3 a_Position;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = vec4(a_Position, 1.0);\n"
        "}\n";

    const char *fragmentSource =
        "#version 430 core\n"

        "out vec4 v_FragColor;\n"

        "void main()\n"
        "{\n"
        "   v_FragColor = vec4(0.9, 0.5, 0.3, 1.0);\n"
        "}\n";

    unsigned int vertexId = ldCompileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentId = ldCompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // TODO: Move this into it's own function;
    ldgl.defaultShaderId = glCreateProgram();
    glAttachShader(ldgl.defaultShaderId, vertexId);
    glAttachShader(ldgl.defaultShaderId, fragmentId);
    glLinkProgram(ldgl.defaultShaderId);

    int success;
    glGetProgramiv(ldgl.defaultShaderId, GL_LINK_STATUS, &success);
    if (!success)
    {
        int maxLength = 0;
        glGetProgramiv(ldgl.defaultShaderId, GL_INFO_LOG_LENGTH, &maxLength);

        if (maxLength > 0)
        {
            int length = 0;
            char log[maxLength];
            glGetProgramInfoLog(ldgl.defaultShaderId, maxLength, &length, log);

            LOG_ERROR("Failed to link shader program: %s", log);
        }

        glDeleteProgram(ldgl.defaultShaderId);
        ldgl.defaultShaderId = 0;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

unsigned int ldCompileShader(const char *src, unsigned int type)
{
    unsigned int id = glCreateShader(type);

    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        if (maxLength > 0)
        {
            int length = 0;
            char log[maxLength];
            glGetShaderInfoLog(id, maxLength, &length, log);

            LOG_ERROR("Failed to compile shader: %s", log);
        }

        glDeleteShader(id);
        id = 0;
    }

    LOG_INFO("Successfully compiled shader: %i", id);

    return id;
}

void ldBegin()
{
    if (ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexCount > 0)
    {
        ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexAlignment = ((ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexCount < 4) ? 1 : (4 - (ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexCount % 4)));
    }
}

void ldVertex2f(float x, float y)
{
    if (ldgl.currentVertices > ldgl.currentBatch->elementCount - 4)
    {

        if (ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexCount % 3 == 0)
        {
            ldCheckRenderBatchLimit(3 + 1);
        }
    }

    int currentVertices = ldgl.currentVertices;

    ldgl.currentBatch->vertices[3 * currentVertices] = x;
    ldgl.currentBatch->vertices[3 * currentVertices + 1] = y;
    ldgl.currentBatch->vertices[3 * currentVertices + 2] = 0.0f;

    ldgl.currentVertices++;
    ldgl.currentBatch->drawCalls[ldgl.currentBatch->drawCounter - 1].vertexCount++;

    // LOG_INFO("Vertices: %d", ldgl.currentVertices);
}

#endif
