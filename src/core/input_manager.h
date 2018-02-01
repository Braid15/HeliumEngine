#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "input.h"
#include "input_listeners.h"

namespace HeliumEngine {

    // @TODO: http://www.glfw.org/docs/latest/input_guide.html
    //        ^^^ Go here to see what needs implementing 

    // @TEMP: I don't know if I wont this to inherit the input subjects or not
    class InputManager final : public IKeyboardInputSubject {
    private:
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

        bool initialize();
        void shutdown();

        bool is_key_pressed(Key key) const;
        bool is_mouse_button_pressed(MouseButton button) const;
        bool is_joystick_button_pressed(JoystickButton button) const;

        float32 get_cursor_x() const;
        float32 get_cursor_y() const;

        std::string get_key_name(Key key) const;

    private:
        InputManager() {}

    // @TEMP: See above
    private:
        std::vector<IKeyboardInputListener*> _keyboard_listeners;

    public:
        void subscribe_listener(IKeyboardInputListener* const listener) override {
            std::vector<IKeyboardInputListener*>::iterator iter = _keyboard_listeners.begin();
            std::vector<IKeyboardInputListener*>::iterator end  = _keyboard_listeners.end();

            while (iter != end) {
                if (*iter == listener) return;
                iter++;
            }

            _keyboard_listeners.push_back(listener);
            std::cout << "SUBSCRIBED\n";
        }

        void unsubscribe_listener(IKeyboardInputListener* const listener) override {
            std::vector<IKeyboardInputListener*>::iterator iter = _keyboard_listeners.begin();
            std::vector<IKeyboardInputListener*>::iterator end  = _keyboard_listeners.end();

            while (iter != end) {
                if (*iter == listener) {
                    _keyboard_listeners.erase(iter);
                    std::cout << "UNSUBSCRIBED\n";
                    return;
                }
                iter++;
            }
        }

        void notify_listeners(Key key, KeyState state) override {
            std::vector<IKeyboardInputListener*>::iterator iter = _keyboard_listeners.begin();
            std::vector<IKeyboardInputListener*>::iterator end  = _keyboard_listeners.end();

            while (iter != end) {
                (*iter)->on_keyboard_input(key, state);
                iter++;
            }
        }
    };


    #ifdef _DEBUG

    class TestKeyboardInputListener : public IKeyboardInputListener {
    public:
        TestKeyboardInputListener() {}

        void on_keyboard_input(Key key, KeyState state) override {
            std::string state_name;
            if (state == KEY_STATE_PRESSED) {
                state_name = "pressed";
            } else if (state == KEY_STATE_RELEASED) {
                state_name = "released";
            }

            std::cout << InputManager::get_singleton().get_key_name(key) << " : " << state_name << "\n";
        }
    };
    #endif
}