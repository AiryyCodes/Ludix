#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "log.h"
#include "ludix.h"
#include "renderer.h"
#include "types.h"

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

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG("Failed to load OpenGL.\n");
        exit(EXIT_FAILURE);
    }

    LOG("Loaded OpenGL %i.%i\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
}

bool window_is_closing()
{
    return glfwWindowShouldClose(platform_state.main_handle);
}

void begin_main_loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    clear_color((Color){0, 0, 0, 255});

    glfwPollEvents();
}

void end_main_loop()
{
    glfwSwapBuffers(platform_state.main_handle);
}

void clear_color(Color color)
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
