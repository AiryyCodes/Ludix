#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "log.h"
#include "ludix.h"
#include "renderer.h"
#include "types.h"
#include "window.h"

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

int window_get_width()
{
    int width, height;
    glfwGetWindowSize(platform_state.main_handle, &width, &height);
    return width;
}

int window_get_height()
{
    int width, height;
    glfwGetWindowSize(platform_state.main_handle, &width, &height);
    return height;
}

int window_get_fb_width()
{
    int width, height;
    glfwGetFramebufferSize(platform_state.main_handle, &width, &height);
    return width;
}

int window_get_fb_height()
{
    int width, height;
    glfwGetFramebufferSize(platform_state.main_handle, &width, &height);
    return height;
}

void begin_main_loop()
{
    clear(GL_COLOR_BUFFER_BIT);
    clear_color((Color){0, 0, 0, 255});
    viewport_set(window_get_fb_width(), window_get_fb_height());

    glfwPollEvents();
}

void end_main_loop()
{
    glfwSwapBuffers(platform_state.main_handle);
}
