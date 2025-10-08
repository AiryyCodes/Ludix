#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "input.h"
#include "log.h"
#include "ludix.h"
#include "renderer.h"
#include "types.h"
#include "window.h"

extern LudixState main_state;

Key convert_glfw_key(int glfw_key);
void key_callback(Key key, bool pressed);

typedef struct
{
    GLFWwindow *main_handle;
} PlatformState;

static PlatformState platform_state = {0};

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Key myKey = convert_glfw_key(key); // You can write a small mapping function
    key_callback(myKey, action != GLFW_RELEASE);
}

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

    glfwSetKeyCallback(platform_state.main_handle, glfw_key_callback);

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
    float currentTime = glfwGetTime();
    main_state.time.delta = currentTime - main_state.time.last;
    main_state.time.last = currentTime;

    clear(GL_COLOR_BUFFER_BIT);
    clear_color((Color){0, 0, 0, 255});
    viewport_set(window_get_fb_width(), window_get_fb_height());

    glfwPollEvents();
}

void end_main_loop()
{
    input_reset();

    glfwSwapBuffers(platform_state.main_handle);
}

static bool key_down[KEY_COUNT] = {false};
static bool key_pressed[KEY_COUNT] = {false};

void input_reset()
{
    memset(key_pressed, 0, sizeof(key_pressed));
}

void key_callback(Key key, bool pressed)
{
    if (key < 0 || key >= KEY_COUNT)
        return;

    if (pressed)
    {
        if (!key_down[key])
            key_pressed[key] = true;
        key_down[key] = true;
    }
    else
    {
        key_down[key] = false;
    }
}

bool is_key_pressed(Key key)
{
    if (key < 0 || key >= KEY_COUNT)
        return false;
    return key_pressed[key];
}

bool is_key_down(Key key)
{
    if (key < 0 || key >= KEY_COUNT)
        return false;
    return key_down[key];
}

Key convert_glfw_key(int glfw_key)
{
    switch (glfw_key)
    {
    // Letters
    case GLFW_KEY_A:
        return KEY_A;
    case GLFW_KEY_B:
        return KEY_B;
    case GLFW_KEY_C:
        return KEY_C;
    case GLFW_KEY_D:
        return KEY_D;
    case GLFW_KEY_E:
        return KEY_E;
    case GLFW_KEY_F:
        return KEY_F;
    case GLFW_KEY_G:
        return KEY_G;
    case GLFW_KEY_H:
        return KEY_H;
    case GLFW_KEY_I:
        return KEY_I;
    case GLFW_KEY_J:
        return KEY_J;
    case GLFW_KEY_K:
        return KEY_K;
    case GLFW_KEY_L:
        return KEY_L;
    case GLFW_KEY_M:
        return KEY_M;
    case GLFW_KEY_N:
        return KEY_N;
    case GLFW_KEY_O:
        return KEY_O;
    case GLFW_KEY_P:
        return KEY_P;
    case GLFW_KEY_Q:
        return KEY_Q;
    case GLFW_KEY_R:
        return KEY_R;
    case GLFW_KEY_S:
        return KEY_S;
    case GLFW_KEY_T:
        return KEY_T;
    case GLFW_KEY_U:
        return KEY_U;
    case GLFW_KEY_V:
        return KEY_V;
    case GLFW_KEY_W:
        return KEY_W;
    case GLFW_KEY_X:
        return KEY_X;
    case GLFW_KEY_Y:
        return KEY_Y;
    case GLFW_KEY_Z:
        return KEY_Z;

    // Numbers
    case GLFW_KEY_0:
        return KEY_0;
    case GLFW_KEY_1:
        return KEY_1;
    case GLFW_KEY_2:
        return KEY_2;
    case GLFW_KEY_3:
        return KEY_3;
    case GLFW_KEY_4:
        return KEY_4;
    case GLFW_KEY_5:
        return KEY_5;
    case GLFW_KEY_6:
        return KEY_6;
    case GLFW_KEY_7:
        return KEY_7;
    case GLFW_KEY_8:
        return KEY_8;
    case GLFW_KEY_9:
        return KEY_9;

    // Function keys
    case GLFW_KEY_F1:
        return KEY_F1;
    case GLFW_KEY_F2:
        return KEY_F2;
    case GLFW_KEY_F3:
        return KEY_F3;
    case GLFW_KEY_F4:
        return KEY_F4;
    case GLFW_KEY_F5:
        return KEY_F5;
    case GLFW_KEY_F6:
        return KEY_F6;
    case GLFW_KEY_F7:
        return KEY_F7;
    case GLFW_KEY_F8:
        return KEY_F8;
    case GLFW_KEY_F9:
        return KEY_F9;
    case GLFW_KEY_F10:
        return KEY_F10;
    case GLFW_KEY_F11:
        return KEY_F11;
    case GLFW_KEY_F12:
        return KEY_F12;

    // Control keys
    case GLFW_KEY_ESCAPE:
        return KEY_ESCAPE;
    case GLFW_KEY_TAB:
        return KEY_TAB;
    case GLFW_KEY_CAPS_LOCK:
        return KEY_CAPS_LOCK;
    case GLFW_KEY_LEFT_SHIFT:
        return KEY_SHIFT_LEFT;
    case GLFW_KEY_RIGHT_SHIFT:
        return KEY_SHIFT_RIGHT;
    case GLFW_KEY_LEFT_CONTROL:
        return KEY_CTRL_LEFT;
    case GLFW_KEY_RIGHT_CONTROL:
        return KEY_CTRL_RIGHT;
    case GLFW_KEY_LEFT_ALT:
        return KEY_ALT_LEFT;
    case GLFW_KEY_RIGHT_ALT:
        return KEY_ALT_RIGHT;
    case GLFW_KEY_LEFT_SUPER:
        return KEY_SUPER_LEFT;
    case GLFW_KEY_RIGHT_SUPER:
        return KEY_SUPER_RIGHT;
    case GLFW_KEY_MENU:
        return KEY_MENU;

    // Whitespace / editing
    case GLFW_KEY_SPACE:
        return KEY_SPACE;
    case GLFW_KEY_ENTER:
        return KEY_ENTER;
    case GLFW_KEY_BACKSPACE:
        return KEY_BACKSPACE;
    case GLFW_KEY_INSERT:
        return KEY_INSERT;
    case GLFW_KEY_DELETE:
        return KEY_DELETE;
    case GLFW_KEY_HOME:
        return KEY_HOME;
    case GLFW_KEY_END:
        return KEY_END;
    case GLFW_KEY_PAGE_UP:
        return KEY_PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:
        return KEY_PAGE_DOWN;

    // Arrows
    case GLFW_KEY_UP:
        return KEY_ARROW_UP;
    case GLFW_KEY_DOWN:
        return KEY_ARROW_DOWN;
    case GLFW_KEY_LEFT:
        return KEY_ARROW_LEFT;
    case GLFW_KEY_RIGHT:
        return KEY_ARROW_RIGHT;

    // Symbols / punctuation
    case GLFW_KEY_MINUS:
        return KEY_MINUS;
    case GLFW_KEY_EQUAL:
        return KEY_EQUAL;
    case GLFW_KEY_LEFT_BRACKET:
        return KEY_LEFT_BRACKET;
    case GLFW_KEY_RIGHT_BRACKET:
        return KEY_RIGHT_BRACKET;
    case GLFW_KEY_BACKSLASH:
        return KEY_BACKSLASH;
    case GLFW_KEY_SEMICOLON:
        return KEY_SEMICOLON;
    case GLFW_KEY_APOSTROPHE:
        return KEY_APOSTROPHE;
    case GLFW_KEY_GRAVE_ACCENT:
        return KEY_GRAVE;
    case GLFW_KEY_COMMA:
        return KEY_COMMA;
    case GLFW_KEY_PERIOD:
        return KEY_PERIOD;
    case GLFW_KEY_SLASH:
        return KEY_SLASH;

    // Numpad
    case GLFW_KEY_NUM_LOCK:
        return KEY_NUM_LOCK;
    case GLFW_KEY_KP_DIVIDE:
        return KEY_KP_DIVIDE;
    case GLFW_KEY_KP_MULTIPLY:
        return KEY_KP_MULTIPLY;
    case GLFW_KEY_KP_SUBTRACT:
        return KEY_KP_SUBTRACT;
    case GLFW_KEY_KP_ADD:
        return KEY_KP_ADD;
    case GLFW_KEY_KP_ENTER:
        return KEY_KP_ENTER;
    case GLFW_KEY_KP_DECIMAL:
        return KEY_KP_DECIMAL;
    case GLFW_KEY_KP_0:
        return KEY_KP_0;
    case GLFW_KEY_KP_1:
        return KEY_KP_1;
    case GLFW_KEY_KP_2:
        return KEY_KP_2;
    case GLFW_KEY_KP_3:
        return KEY_KP_3;
    case GLFW_KEY_KP_4:
        return KEY_KP_4;
    case GLFW_KEY_KP_5:
        return KEY_KP_5;
    case GLFW_KEY_KP_6:
        return KEY_KP_6;
    case GLFW_KEY_KP_7:
        return KEY_KP_7;
    case GLFW_KEY_KP_8:
        return KEY_KP_8;
    case GLFW_KEY_KP_9:
        return KEY_KP_9;

    // Misc
    case GLFW_KEY_PRINT_SCREEN:
        return KEY_PRINT_SCREEN;
    case GLFW_KEY_SCROLL_LOCK:
        return KEY_SCROLL_LOCK;
    case GLFW_KEY_PAUSE:
        return KEY_PAUSE;

    default:
        return KEY_UNKNOWN;
    }
}
