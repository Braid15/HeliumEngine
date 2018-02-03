#pragma once

#include <helium_std.h>
#include "input.h"

namespace HeliumEngine {

    // @TODO: I don't know if these are needed since you can call InputManager directly and get 
    //        input status, but i'll keep them here just in case.
    class IMouseInputListener {
    public:
        virtual void on_mouse_input(MouseButton button, ButtonState state, float32 x_pos, float32 y_pos) = 0;
        virtual ~IMouseInputListener() {}
    };

    class IKeyboardInputListener {
    public:
        virtual void on_keyboard_input(Key key, KeyState state) = 0;
        virtual ~IKeyboardInputListener() {}
    };

    class IKeyPressedInputListener {
    public:
        virtual void on_key_pressed_input(Key key) = 0;
        virtual ~IKeyPressedInputListener() {}
    };

    class IKeyReleasedInputListener {
    public:
        virtual void on_key_released_input(Key key) = 0;
        virtual ~IKeyReleasedInputListener() {}
    };
}