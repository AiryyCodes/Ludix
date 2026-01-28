#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "platform/internal/core.h"
#include "ldgl.h"
#include "ludix.h"

#ifndef MAX_LOG_MSG_LENGTH
#define MAX_LOG_MSG_LENGTH 256 // Max length of one log message
#endif

#if defined(PLATFORM_DESKTOP)
#define PLATFORM_DESKTOP_GLFW
#endif

#if defined(PLATFORM_DESKTOP_GLFW)
#include "platform/platform_glfw.c"
#endif

CoreState core = {0};

extern int InitPlatform();

// Platform

void InitWindow(int width, int height, const char *title)
{
    LOG_INFO("Initializing platform...");

    core.window.title = title;
    core.window.width = width;
    core.window.height = height;

    int error = InitPlatform();
    if (error)
    {
        LOG_ERROR("Failed to initialize platform!\n");
        return;
    }
}

// Rendering

void BeginFrame()
{
}

void EndFrame()
{
    ldDrawActiveRenderBatch();

    SwapBuffers();
    PollEvents();
}

void DrawTriangle(int x, int y)
{
    ldBegin();
    ldVertex2f(x + -0.5f, y + -0.5f);
    ldVertex2f(x + 0.5f, y + -0.5f);
    ldVertex2f(x + 0.0f, y + 0.5f);
}

void DrawRectangle(int x, int y, int width, int height)
{
}

// Logging

void ConsoleLog(LogLevel level, const char *text, ...)
{
    va_list args;
    va_start(args, text);

    char buffer[MAX_LOG_MSG_LENGTH] = {0};

    switch (level)
    {
    case LOG_INFO:
        strncpy(buffer, "INFO: ", 7);
        break;
    case LOG_WARNING:
        strncpy(buffer, "WARNING: ", 10);
        break;
    case LOG_ERROR:
        strncpy(buffer, "ERROR: ", 8);
        break;
    }

    unsigned int textLength = (unsigned int)strlen(text);

    // -1 for null terminator
    size_t remaining = MAX_LOG_MSG_LENGTH - strlen(buffer) - 1;
    size_t copyLength = (textLength < remaining) ? textLength : remaining;

    memcpy(buffer + strlen(buffer), text, copyLength);
    buffer[strlen(buffer) + copyLength] = '\0';
    strcat(buffer, "\n");
    vprintf(buffer, args);

    va_end(args);
}
