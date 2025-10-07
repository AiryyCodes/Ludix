#pragma once

#include "Renderer/mesh.h"
#include "ecs_types.h"

#include <flecs.h>

#define ECS_DECLARE_COMPONENT(Type) \
    ECS_COMPONENT_DECLARE(Type);

#define ECS_DECLARE_COMPONENT_H(Type) \
    extern ECS_COMPONENT_DECLARE(Type);

#define ECS_DEFINE_COMPONENT(World, Type) \
    ECS_COMPONENT_DEFINE(World, Type);

#define ECS_ADD_COMPONENT(Entity, Type, Data) \
    ecs_add_component(Entity, (void *)(&(Type)Data), sizeof((Type)Data), ecs_id(Type));

typedef struct
{
    Mesh *mesh;
} MeshRenderer;

ECS_DECLARE_COMPONENT_H(MeshRenderer);

void ecs_tick(float delta);
void ecs_destroy();

Entity ecs_create_entity();
void ecs_add_component(Entity e, void *component_data, size_t size, ecs_entity_t component_id);

void rendering_system(ecs_iter_t *it);
