#include "ecs.h"
#include "ludix.h"

#include <flecs.h>

extern LudixState main_state;

void ecs_tick(float delta)
{
    ecs_progress(main_state.world, delta);
}

void ecs_destroy()
{
    ecs_fini(main_state.world);
}

Entity ecs_create_entity()
{
    return ecs_new(main_state.world);
}

void ecs_add_component(Entity e, void *component_data, size_t size, ecs_entity_t component_id)
{
    ecs_set_id(main_state.world, e, component_id, size, component_data);
}

void rendering_system(ecs_iter_t *it)
{
    MeshRenderer *mesh_renderer = ecs_field(it, MeshRenderer, 0);

    for (int i = 0; i < it->count; i++)
    {
        mesh_draw(mesh_renderer[i].mesh);
    }
}
