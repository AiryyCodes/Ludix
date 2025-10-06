#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "ludix.h"

typedef struct
{
    GLFWwindow *main_handle;
} PlatformState;

static PlatformState platform_state = {0};

void platform_init()
{
    if (!glfwInit())
    {
        LOG("Failed to initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }
}

void window_init(const char *title, int width, int height)
{
    platform_init();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    platform_state.main_handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (platform_state.main_handle == NULL)
    {
        LOG("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_SUCCESS);
        return;
    }

    glfwMakeContextCurrent(platform_state.main_handle);
}

bool window_is_closing()
{
    return glfwWindowShouldClose(platform_state.main_handle);
}

void begin_main_loop()
{
    glfwPollEvents();
}

void end_main_loop()
{
    glfwSwapBuffers(platform_state.main_handle);
}
