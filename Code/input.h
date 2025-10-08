#pragma once

#include "Math/vector.h"
#include "types.h"

typedef enum
{
    // Letters
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,

    // Numbers
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    // Function keys
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    // Control keys
    KEY_ESCAPE,
    KEY_TAB,
    KEY_CAPS_LOCK,
    KEY_SHIFT_LEFT,
    KEY_SHIFT_RIGHT,
    KEY_CTRL_LEFT,
    KEY_CTRL_RIGHT,
    KEY_ALT_LEFT,
    KEY_ALT_RIGHT,
    KEY_SUPER_LEFT,
    KEY_SUPER_RIGHT,
    KEY_MENU,

    // Whitespace / editing
    KEY_SPACE,
    KEY_ENTER,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,

    // Arrows
    KEY_ARROW_UP,
    KEY_ARROW_DOWN,
    KEY_ARROW_LEFT,
    KEY_ARROW_RIGHT,

    // Symbols
    KEY_MINUS,
    KEY_EQUAL,
    KEY_LEFT_BRACKET,
    KEY_RIGHT_BRACKET,
    KEY_BACKSLASH,
    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_GRAVE,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,

    // Numpad
    KEY_NUM_LOCK,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_SUBTRACT,
    KEY_KP_ADD,
    KEY_KP_ENTER,
    KEY_KP_DECIMAL,
    KEY_KP_0,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,

    // Misc
    KEY_PRINT_SCREEN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE,

    KEY_UNKNOWN,
    KEY_COUNT
} Key;

typedef enum
{
    BUTTON_LEFT,

    BUTTON_UNKNOWN,
    BUTTON_COUNT
} Button;

void input_reset();

bool is_key_pressed(Key key);
bool is_key_down(Key key);

bool is_button_pressed(Button button);
bool is_button_down(Button button);

fvec2 get_mouse_position();

float get_scroll_x();
float get_scroll_y();
