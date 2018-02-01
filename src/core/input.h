#pragma once

#include <helium_std.h>

namespace HeliumEngine {

    typedef enum {
        KEY_STATE_NULL     = -1,
        KEY_STATE_RELEASED = 0,
        KEY_STATE_PRESSED,
    } KeyState;

    // Pretty much 1:1 with GLFW_KEY #defines
    typedef enum {
        KEY_NULL       = -1,
        KEY_FIRST      = 0,
        KEY_SPACE      = 32,
        KEY_APOSTROPHE = 39,
        KEY_COMMA      = 44,
        KEY_MINUS,
        KEY_PERIOD,
        KEY_SLASH,
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
        KEY_SEMICOLON = 59,
        KEY_EQUAL     = 61,
        KEY_A         = 65,
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
        KEY_LEFT_BRACKET,
        KEY_BACKSLASH,
        KEY_RIGHT_BRACKET,
        KEY_ACCENT = 96,

        // Not defined by GLFW since this key needs a modifier
        KEY_TILDE = 126,

        KEY_ESCAPE = 256,
        KEY_ENTER,
        KEY_TAB,
        KEY_BACKSPACE,
        KEY_INSERT,
        KEY_DELETE,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_DOWN,
        KEY_UP,
        KEY_PAGE_UP,
        KEY_PAGE_DOWN,
        KEY_HOME,
        KEY_END,
        KEY_CAPS_LOCK = 280,
        KEY_SCROLL_LOCK,
        KEY_NUM_LOCK,
        KEY_PRINT_SCREEN,
        KEY_PAUSE,
        KEY_F1 = 290,
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

        KEY_KP_0 = 320,
        KEY_KP_1,
        KEY_KP_2,
        KEY_KP_3,
        KEY_KP_4,
        KEY_KP_5,
        KEY_KP_6,
        KEY_KP_7,
        KEY_KP_8,
        KEY_KP_9,
        KEY_KP_DECIMAL,
        KEY_KP_DIVIDE,
        KEY_KP_MULTIPLY,
        KEY_KP_SUBTRACT,
        KEY_KP_ADD,
        KEY_KP_ENTER,
        KEY_KP_EQUAL,

        KEY_LEFT_SHIFT = 340,
        KEY_LEFT_CONTROL,
        KEY_LEFT_ALT,
        KEY_RIGHT_SHIFT,
        KEY_RIGHT_CONTROL,
        KEY_RIGHT_ALT,

        KEY_LAST
    } Key;

    struct KeyboardData final {
        KeyState keys[KEY_LAST];

        KeyboardData();
    };

    typedef enum {
        BUTTON_STATE_NULL     = -1,
        BUTTON_STATE_RELEASED = 0,
        BUTTON_STATE_PRESSED,
    } ButtonState;

    typedef enum {
        MOUSE_BUTTON_NULL  = -1,
        MOUSE_BUTTON_FIRST = 0,
        MOUSE_BUTTON_1     = 0,
        MOUSE_BUTTON_2,
        MOUSE_BUTTON_3,
        MOUSE_BUTTON_4,
        MOUSE_BUTTON_5,
        MOUSE_BUTTON_6,
        MOUSE_BUTTON_8,
        MOUSE_BUTTON_LAST,
        MOUSE_BUTTON_LEFT   = MOUSE_BUTTON_1,
        MOUSE_BUTTON_RIGHT  = MOUSE_BUTTON_2,
        MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
    } MouseButton;

    struct MouseData final {
        ButtonState buttons[MOUSE_BUTTON_LAST];

        // @TODO: Use Vector2 when it's implemented
        float32 cursor_x;
        float32 cursor_y;

        MouseData();
    };

    typedef enum {
        JOYSTICK_BUTTON_NULL  = -1,
        JOYSTICK_BUTTON_FIRST = 0,
        JOYSTICK_BUTTON_1     = 0,
        JOYSTICK_BUTTON_2,
        JOYSTICK_BUTTON_3,
        JOYSTICK_BUTTON_4,
        JOYSTICK_BUTTON_5,
        JOYSTICK_BUTTON_6,
        JOYSTICK_BUTTON_7,
        JOYSTICK_BUTTON_8,
        JOYSTICK_BUTTON_9,
        JOYSTICK_BUTTON_10,
        JOYSTICK_BUTTON_11,
        JOYSTICK_BUTTON_12,
        JOYSTICK_BUTTON_13,
        JOYSTICK_BUTTON_14,
        JOYSTICK_BUTTON_15,
        JOYSTICK_BUTTON_16,
        JOYSTICK_BUTTON_LAST
    } JoystickButton;

    struct JoystickData final {
        ButtonState buttons[JOYSTICK_BUTTON_LAST];

        JoystickData();
    };


    
}