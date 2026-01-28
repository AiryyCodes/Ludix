#pragma once

#define LDGL_IMPLEMENTATION
#include "ldgl.h"
#include "internal/core.h"
#include "ludix.h"

#include <GLFW/glfw3.h>

typedef struct
{
    GLFWwindow *handle;
} PlatformState;

PlatformState platform = {0};

int InitPlatform()
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwDefaultWindowHints();

    platform.handle = glfwCreateWindow(core.window.width, core.window.height, core.window.title, NULL, NULL);
    if (platform.handle == NULL)
    {
        LOG_ERROR("Failed to create GLFW window!\n");
        return -1;
    }

    glfwMakeContextCurrent(platform.handle);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        LOG_ERROR("Failed to initialize OpenGL contex");
        return -1;
    }

    LOG_INFO("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    ldglInit();

    core.window.ready = true;

    return 0;
}

bool IsWindowClosing()
{
    if (!core.window.ready)
        return true;

    return glfwWindowShouldClose(platform.handle);
}

void PollEvents()
{
    glfwPollEvents();
}

void SwapBuffers()
{
    if (!core.window.ready)
        return;

    glfwSwapBuffers(platform.handle);
}
