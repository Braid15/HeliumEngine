#include "input_manager.h"
#include "window_manager.h"

namespace HeliumEngine {

    static Key convert_glfw_key_to_helium_key(int glfw_key) {
        switch (glfw_key) {
            case GLFW_KEY_SPACE: return KEY_SPACE;
            case GLFW_KEY_APOSTROPHE: return KEY_APOSTROPHE;
            case GLFW_KEY_COMMA : return KEY_COMMA;
            case GLFW_KEY_MINUS : return KEY_MINUS;
            case GLFW_KEY_PERIOD : return KEY_PERIOD;
            case GLFW_KEY_SLASH : return KEY_SLASH;
            case GLFW_KEY_0 : return KEY_0;
            case GLFW_KEY_1 : return KEY_1;
            case GLFW_KEY_2 : return KEY_2; 
            case GLFW_KEY_3 : return KEY_3;
            case GLFW_KEY_4 : return KEY_4;
            case GLFW_KEY_5 : return KEY_5;
            case GLFW_KEY_6 : return KEY_6;
            case GLFW_KEY_7 : return KEY_7;
            case GLFW_KEY_8 : return KEY_8;
            case GLFW_KEY_9 : return KEY_9;
            default:
            {
                std::cout << "convert_glfw_key_to_helium_key() FINISH!!\n";
                return KEY_NULL;
            }
        }
        return KEY_NULL;
    }

    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        KeyboardData* const keyboard_data = &InputManager::get_singleton()._keyboard_data;
    
        KeyState state = (action == GLFW_PRESS || action == GLFW_REPEAT) ? KEY_STATE_PRESSED : KEY_STATE_RELEASED;

        // Handle tilde key
        if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_GRAVE_ACCENT) {
            keyboard_data->keys[KEY_TILDE] = state;
        } else {
            keyboard_data->keys[key] = state;
        }

        InputManager::get_singleton().notify_listeners(convert_glfw_key_to_helium_key(key), state);
    }

    static void glfw_mouse_cursor_callback(GLFWwindow* window, double x_pos, double y_pos) {
        MouseData* const mouse_data = &InputManager::get_singleton()._mouse_data;

        mouse_data->cursor_x = static_cast<float32>(x_pos);
        mouse_data->cursor_y = static_cast<float32>(y_pos);
    }

    static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        MouseData* const mouse_data = &InputManager::get_singleton()._mouse_data;

        ButtonState state = (action == GLFW_PRESS || action == GLFW_REPEAT) ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;

        mouse_data->buttons[button] = state;
    }

    static void glfw_scroll_wheel_callback(GLFWwindow* window, double x_offset, double y_offset) {
        // idk what to do yet
        std::cout << "glfw_scroll_wheel_callback() UNIMPLEMENTED!!!\n";
    }

    static void glfw_joystick_connection_callback(int joystick_id, int event_type) {
        std::cout << "glfw_joystick_connection_callback() UNIMPLEMENTED!!!\n";

        if (event_type == GLFW_CONNECTED) {
            std::cout << "Joystick: " << joystick_id << " was connected.\n";
        } else if (event_type == GLFW_DISCONNECTED) {
            std::cout << "Joystick: " << joystick_id << " was disconnected.\n";
        }
    }

    InputManager InputManager::_singleton;

    InputManager& InputManager::get_singleton() {
        return _singleton;
    }

    bool InputManager::initialize() {
        GLFWwindow* window = &WindowManager::get_singleton().get_glfw_window();
        assert(window);

        glfwSetKeyCallback(window, &glfw_key_callback);
        glfwSetCursorPosCallback(window, &glfw_mouse_cursor_callback);
        glfwSetMouseButtonCallback(window, &glfw_mouse_button_callback);
        glfwSetScrollCallback(window, &glfw_scroll_wheel_callback);
        glfwSetJoystickCallback(&glfw_joystick_connection_callback);

        return true;
    }

    void InputManager::shutdown() {
        // Nothing to cleanup
    }

    bool InputManager::is_key_pressed(Key key) const {
        if (key == KEY_NULL || key == KEY_LAST) return false;

        return _keyboard_data.keys[key] == KEY_STATE_PRESSED;
    }

    bool InputManager::is_mouse_button_pressed(MouseButton button) const {
        if (button == MOUSE_BUTTON_NULL || button == MOUSE_BUTTON_LAST) return false;

        return _mouse_data.buttons[button] == BUTTON_STATE_PRESSED;
    }

    bool InputManager::is_joystick_button_pressed(JoystickButton button) const {
        if (button == JOYSTICK_BUTTON_NULL || button == JOYSTICK_BUTTON_LAST) return false;

        return _joystick_data.buttons[button] == BUTTON_STATE_PRESSED;
    }

    float32 InputManager::get_cursor_x() const {
        return _mouse_data.cursor_x;
    }

    float32 InputManager::get_cursor_y() const {
        return _mouse_data.cursor_y;
    }

    std::string InputManager::get_key_name(Key key) const {
        // Check if printable character
        if (!(0 <= key && key < KEY_ESCAPE)) return std::string();

        return std::string(glfwGetKeyName(key, 0));
    }
}