#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "input.h"
#include "input_listeners.h"

namespace HeliumEngine {

    // @TODO: http://www.glfw.org/docs/latest/input_guide.html
    //        ^^^ Go here to see what needs implementing 

    class InputManager final {
    private:
        friend class Engine;

        friend void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        friend void glfw_mouse_cursor_callback(GLFWwindow* window, double x_pos, double y_pos);
        friend void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        friend void glfw_scroll_wheel_callback(GLFWwindow* window, double x_offset, double y_offset);
        friend void glfw_joystick_connection_callback(int joystick_id, int event_type);

        static InputManager _singleton;

        MouseData _mouse_data;
        KeyboardData _keyboard_data;
        // @TODO: This should be a map since multiple joysticks can be attached
        JoystickData _joystick_data;
    public:
        InputManager(const InputManager&) = delete;
        ~InputManager() {}

        InputManager& operator=(const InputManager&) = delete;

        static InputManager& get_singleton();

        bool is_key_pressed(const Key key) const;
        bool is_mouse_button_pressed(const MouseButton button) const;
        bool is_joystick_button_pressed(const JoystickButton button) const;

        vec2 get_cursor_position() const;

        std::string get_key_name(const Key key) const;

        MouseData& get_mouse_data();
        KeyboardData& get_keyboard_data();
        JoystickData& get_joystick_data();

    private:
        InputManager() {}

        bool initialize();
        void shutdown();
        void refresh_data();

    };
}