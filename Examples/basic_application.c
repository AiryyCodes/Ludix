#include <stdlib.h>

#include "Renderer/mesh.h"
#include "Renderer/shader.h"
#include "ecs.h"
#include "ludix.h"

const Vertex TRIANGLE_VERTICES[] = {
    {
        {-0.5f, -0.5f, 0.0f},
    },
    {
        {0.5f, -0.5f, 0.0f},
    },
    {
        {0.0f, 0.5f, 0.0f},
    },
};

int main()
{
    window_init("Basic Application", 800, 600);

    Shader *shader = shader_create("Resources/Shaders/Main.vert", "Resources/Shaders/Main.frag");

    Mesh *triangle_mesh = mesh_create(TRIANGLE_VERTICES, 3);

    ludix_init();

    Entity entity1 = ecs_create_entity();
    ECS_ADD_COMPONENT(entity1, MeshRenderer, {triangle_mesh});

    while (!window_is_closing())
    {
        begin_main_loop();

        shader_begin(shader);

        ecs_tick(0);

        shader_end();

        end_main_loop();
    }

    mesh_destroy(triangle_mesh);
    shader_destroy(shader);

    ecs_destroy();

    return EXIT_SUCCESS;
}
