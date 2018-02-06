#pragma once

#include <helium_std.h>
#include "core/math/math.h"

namespace HeliumEngine {

    typedef enum {
        KEY_STATE_NULL     = -1,
        KEY_STATE_RELEASED = 0,
        KEY_STATE_PRESSED,
        KEY_STATE_HELD, 
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
        KeyState last_event;
        Key last_event_key;

        KeyboardData();
    };

    typedef enum {
        BUTTON_STATE_NULL     = -1,
        BUTTON_STATE_RELEASED = 0,
        BUTTON_STATE_PRESSED,
        BUTTON_STATE_HELD
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
        MOUSE_BUTTON_7,
        MOUSE_BUTTON_8,
        MOUSE_BUTTON_LAST,
        MOUSE_BUTTON_LEFT   = MOUSE_BUTTON_1,
        MOUSE_BUTTON_RIGHT  = MOUSE_BUTTON_2,
        MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
    } MouseButton;

    typedef enum {
        MOUSE_EVENT_NULL,
        MOUSE_EVENT_MOTION,
        MOUSE_EVENT_BUTTON_UP,
        MOUSE_EVENT_BUTTON_DOWN,
        MOUSE_EVENT_BUTTON_HELD,
        MOUSE_EVENT_SCROLL
    } MouseEvent;

    struct MouseData final {
        ButtonState buttons[MOUSE_BUTTON_LAST];
        glm::vec2 position;
        MouseEvent last_event;
        MouseButton last_event_button;
        float32 scroll_offset_x;
        float32 scroll_offset_y;

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

    // @TODO: Make this into a class instead of a struct and refactor
    class InputData final {
    private:
        KeyboardData& keyboard;
        MouseData& mouse;
        JoystickData& joystick;

    public:
        InputData() = delete;
        InputData(const InputData&) = delete;
        InputData& operator=(const InputData&) = delete;

        InputData(KeyboardData& k, MouseData& m, JoystickData& j) :
            keyboard(k), mouse(m), joystick(j) 
        {}

        bool key_pressed(const Key key) {
            if (keyboard.last_event != KEY_STATE_PRESSED) return false;
            return keyboard.last_event_key == key;
        }

        const Key& key() {
            return keyboard.last_event_key;
        }

        bool key_pressed() {
            return keyboard.last_event == KEY_STATE_PRESSED;
        }

        bool key_released() {
            return keyboard.last_event == KEY_STATE_RELEASED;
        }

        bool key_held(const Key key) {
            return keyboard.keys[key] == KEY_STATE_HELD;
        }

        bool key_released(const Key key) {
            if (keyboard.last_event != KEY_STATE_RELEASED) return false;
            return keyboard.last_event_key == key;
        }

        bool mouse_moved() {
            return mouse.last_event == MOUSE_EVENT_MOTION;
        }

        vec2& mouse_position() {
            return mouse.position;
        }

        bool mouse_scroll() {
            return mouse.last_event == MOUSE_EVENT_SCROLL;
        }

        bool mouse_scroll_up() {
            if (mouse.last_event != MOUSE_EVENT_SCROLL) return false;
            return mouse.scroll_offset_y > 0;
        }

        bool mouse_scroll_down() {
            if (mouse.last_event != MOUSE_EVENT_SCROLL) return false;
            return mouse.scroll_offset_y < 0;
        }

        bool mouse_drag(const MouseButton button) {
            return mouse_click_held(button) && mouse_moved();
        }

        bool mouse_click_down(const MouseButton button) {
            if (mouse.last_event != MOUSE_EVENT_BUTTON_DOWN) return false;
            return mouse.last_event_button == button;
        }

        bool mouse_click_up(const MouseButton button) {
            if (mouse.last_event != MOUSE_EVENT_BUTTON_UP) return false;
            return mouse.last_event_button == button;
        }

        bool mouse_click_held(const MouseButton button) {
            return mouse.buttons[button] == BUTTON_STATE_PRESSED;
        }

        bool button_pressed(const JoystickButton button) {
            std::cout << "[InputData] UNIMPLEMENTED\n";
        }

        bool button_released(const JoystickButton button) {
            std::cout << "[InputData] UNIMPLEMENTED\n";
        }

        bool button_held(const JoystickButton button) {
            std::cout << "[InputData] UNIMPLEMENTED\n";
        }


    };
}