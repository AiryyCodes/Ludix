#pragma once

#include "Math/vector.h"
#include "types.h"

typedef struct
{
    fvec3 position;
} Vertex;

typedef struct
{
    void *handle;
    void *vertex_buffer;

    u32 num_vertices;
} Mesh;

Mesh *mesh_create(const Vertex vertices[], u32 num_vertices);
void mesh_destroy(Mesh *mesh);

void mesh_draw(const Mesh *mesh);
