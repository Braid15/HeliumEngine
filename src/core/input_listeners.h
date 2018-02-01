#pragma once

#include <helium_std.h>
#include "input.h"

namespace HeliumEngine {

    class IMouseInputListener {
    public:
        virtual void on_mouse_input(MouseButton button, ButtonState state, float32 x_pos, float32 y_pos) = 0;
        virtual ~IMouseInputListener() {}
    };

    class IMouseInputSubject {
    public:
        virtual void notify_listeners() = 0;
        virtual void subscribe_listener(IMouseInputListener* const listener)   = 0;
        virtual void unsubscribe_listener(IMouseInputListener* const listener) = 0;
        virtual ~IMouseInputSubject() {}
    };

    class IKeyboardInputListener {
    public:
        virtual void on_keyboard_input(Key key, KeyState state) = 0;
        virtual ~IKeyboardInputListener() {}
    };

    class IKeyboardInputSubject {
    public:
        virtual void notify_listeners(Key key, KeyState state) = 0;
        virtual void subscribe_listener(IKeyboardInputListener* const listener)   = 0;
        virtual void unsubscribe_listener(IKeyboardInputListener* const listener) = 0;
        virtual ~IKeyboardInputSubject() {}
    };

    class IKeyPressedInputListener {
    public:
        virtual void on_key_pressed_input(Key key) = 0;
        virtual ~IKeyPressedInputListener() {}
    };

    class IKeyPressedInputSubject {
    public:
        virtual void notify_listeners() = 0;
        virtual void subscribe_listener(IKeyPressedInputListener* const listener)   = 0;
        virtual void unsubscribe_listener(IKeyPressedInputListener* const listener) = 0;
        virtual ~IKeyPressedInputSubject() {}
    };

    class IKeyReleasedInputListener {
    public:
        virtual void on_key_released_input(Key key) = 0;
        virtual ~IKeyReleasedInputListener() {}
    };

    class IKeyReleasedInputSubject {
    public:
        virtual void notify_listeners() = 0;
        virtual void subscribe_listener(IKeyReleasedInputListener* const listener)   = 0;
        virtual void unsubscribe_listener(IKeyReleasedInputListener* const listener) = 0;
        virtual ~IKeyReleasedInputSubject() {}
    };
}