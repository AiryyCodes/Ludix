#pragma once

#include <stdbool.h>

// clang-format off
#if defined(_WIN32)
    #if defined(__TINYC__)
        #define __declspec(x) __attribute__((x))
    #endif
    #if defined(BUILD_LIBTYPE_SHARED)
        #define LUDIX_API __declspec(dllexport)     // Building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define LUDIX_API __declspec(dllimport)     // Using the library as a Win32 shared library (.dll)
    #endif
#else
    #if defined(BUILD_LIBTYPE_SHARED)
        #define LUDIX_API __attribute__((visibility("default"))) // Building as a Unix shared library (.so/.dylib)
    #endif
#endif

#ifndef LUDIX_API
    #define LUDIX_API
#endif
// clang-format on

#define LOG_INFO(...) ConsoleLog(LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(...) ConsoleLog(LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(...) ConsoleLog(LOG_ERROR, __VA_ARGS__)

typedef enum
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
} LogLevel;

// Platform
LUDIX_API void InitWindow(int width, int height, const char *title);
LUDIX_API bool IsWindowClosing();
LUDIX_API void PollEvents();

// Rendering
LUDIX_API void BeginFrame();
LUDIX_API void EndFrame();
LUDIX_API void SwapBuffers();

LUDIX_API void DrawTriangle(int x, int y);
LUDIX_API void DrawRectangle(int x, int y, int width, int height);

// Logging
LUDIX_API void ConsoleLog(LogLevel level, const char *text, ...);
