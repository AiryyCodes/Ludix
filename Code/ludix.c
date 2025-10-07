#include "ludix.h"
#include "ecs.h"

#include <flecs.h>

LudixState main_state;

ECS_DECLARE_COMPONENT(MeshRenderer);

void ludix_init()
{
    main_state.world = ecs_init();

    ECS_DEFINE_COMPONENT(main_state.world, MeshRenderer);
    ECS_SYSTEM(main_state.world, rendering_system, EcsOnUpdate, MeshRenderer);
}
