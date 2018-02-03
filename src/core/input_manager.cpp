#include "input_manager.h"
#include "window_manager.h"

namespace HeliumEngine {

    static Key convert_glfw_key_to_helium_key(int glfw_key) {
        switch (glfw_key) {
            case GLFW_KEY_SPACE         : return KEY_SPACE;
            case GLFW_KEY_APOSTROPHE    : return KEY_APOSTROPHE;
            case GLFW_KEY_COMMA         : return KEY_COMMA;
            case GLFW_KEY_MINUS         : return KEY_MINUS;
            case GLFW_KEY_PERIOD        : return KEY_PERIOD;
            case GLFW_KEY_SLASH         : return KEY_SLASH;
            case GLFW_KEY_0             : return KEY_0;
            case GLFW_KEY_1             : return KEY_1;
            case GLFW_KEY_2             : return KEY_2; 
            case GLFW_KEY_3             : return KEY_3;
            case GLFW_KEY_4             : return KEY_4;
            case GLFW_KEY_5             : return KEY_5;
            case GLFW_KEY_6             : return KEY_6;
            case GLFW_KEY_7             : return KEY_7;
            case GLFW_KEY_8             : return KEY_8;
            case GLFW_KEY_9             : return KEY_9;
            case GLFW_KEY_SEMICOLON     : return KEY_SEMICOLON;
            case GLFW_KEY_EQUAL         : return KEY_EQUAL;
            case GLFW_KEY_A             : return KEY_A;
            case GLFW_KEY_B             : return KEY_B;
            case GLFW_KEY_C             : return KEY_C;
            case GLFW_KEY_D             : return KEY_D;
            case GLFW_KEY_E             : return KEY_E;
            case GLFW_KEY_F             : return KEY_F;
            case GLFW_KEY_G             : return KEY_G;
            case GLFW_KEY_H             : return KEY_H;
            case GLFW_KEY_I             : return KEY_I;
            case GLFW_KEY_J             : return KEY_J;
            case GLFW_KEY_K             : return KEY_K;
            case GLFW_KEY_L             : return KEY_L;
            case GLFW_KEY_M             : return KEY_M;
            case GLFW_KEY_N             : return KEY_N;
            case GLFW_KEY_O             : return KEY_O;
            case GLFW_KEY_P             : return KEY_P;
            case GLFW_KEY_Q             : return KEY_Q;
            case GLFW_KEY_R             : return KEY_R;
            case GLFW_KEY_S             : return KEY_S;
            case GLFW_KEY_T             : return KEY_T;
            case GLFW_KEY_U             : return KEY_U;
            case GLFW_KEY_V             : return KEY_V;
            case GLFW_KEY_W             : return KEY_W;
            case GLFW_KEY_X             : return KEY_X;
            case GLFW_KEY_Y             : return KEY_Y;
            case GLFW_KEY_Z             : return KEY_Z;
            case GLFW_KEY_LEFT_BRACKET  : return KEY_LEFT_BRACKET;
            case GLFW_KEY_BACKSLASH     : return KEY_BACKSLASH;
            case GLFW_KEY_RIGHT_BRACKET : return KEY_RIGHT_BRACKET;
            case GLFW_KEY_GRAVE_ACCENT  : return KEY_ACCENT;
            case GLFW_KEY_ESCAPE        : return KEY_ESCAPE;
            case GLFW_KEY_ENTER         : return KEY_ENTER;
            case GLFW_KEY_TAB           : return KEY_TAB;
            case GLFW_KEY_BACKSPACE     : return KEY_BACKSPACE;
            case GLFW_KEY_INSERT        : return KEY_INSERT;
            case GLFW_KEY_DELETE        : return KEY_DELETE;
            case GLFW_KEY_RIGHT         : return KEY_RIGHT;
            case GLFW_KEY_LEFT          : return KEY_LEFT;
            case GLFW_KEY_DOWN          : return KEY_DOWN;
            case GLFW_KEY_UP            : return KEY_UP;
            case GLFW_KEY_PAGE_UP       : return KEY_PAGE_UP;
            case GLFW_KEY_PAGE_DOWN     : return KEY_PAGE_DOWN;
            case GLFW_KEY_HOME          : return KEY_HOME;
            case GLFW_KEY_END           : return KEY_END;
            case GLFW_KEY_CAPS_LOCK     : return KEY_CAPS_LOCK;
            case GLFW_KEY_SCROLL_LOCK   : return KEY_SCROLL_LOCK;
            case GLFW_KEY_NUM_LOCK      : return KEY_NUM_LOCK;
            case GLFW_KEY_PRINT_SCREEN  : return KEY_PRINT_SCREEN;
            case GLFW_KEY_PAUSE         : return KEY_PAUSE;
            case GLFW_KEY_F1            : return KEY_F1;
            case GLFW_KEY_F2            : return KEY_F2; 
            case GLFW_KEY_F3            : return KEY_F3;
            case GLFW_KEY_F4            : return KEY_F4;
            case GLFW_KEY_F5            : return KEY_F5;
            case GLFW_KEY_F6            : return KEY_F6;
            case GLFW_KEY_F7            : return KEY_F7;
            case GLFW_KEY_F8            : return KEY_F8;
            case GLFW_KEY_F9            : return KEY_F9;
            case GLFW_KEY_F10           : return KEY_F10;
            case GLFW_KEY_F11           : return KEY_F11;
            case GLFW_KEY_F12           : return KEY_F12;
            case GLFW_KEY_KP_0          : return KEY_KP_0;
            case GLFW_KEY_KP_1          : return KEY_KP_1;
            case GLFW_KEY_KP_2          : return KEY_KP_2;
            case GLFW_KEY_KP_3          : return KEY_KP_3;
            case GLFW_KEY_KP_4          : return KEY_KP_4;
            case GLFW_KEY_KP_5          : return KEY_KP_5;
            case GLFW_KEY_KP_6          : return KEY_KP_6;
            case GLFW_KEY_KP_7          : return KEY_KP_7;
            case GLFW_KEY_KP_8          : return KEY_KP_8;
            case GLFW_KEY_KP_9          : return KEY_KP_9;
            case GLFW_KEY_KP_DECIMAL    : return KEY_KP_DECIMAL;
            case GLFW_KEY_KP_DIVIDE     : return KEY_KP_DIVIDE;
            case GLFW_KEY_KP_MULTIPLY   : return KEY_KP_MULTIPLY;
            case GLFW_KEY_KP_SUBTRACT   : return KEY_KP_SUBTRACT;
            case GLFW_KEY_KP_ADD        : return KEY_KP_ADD;
            case GLFW_KEY_KP_ENTER      : return KEY_KP_ENTER;
            case GLFW_KEY_KP_EQUAL      : return KEY_KP_EQUAL;
            case GLFW_KEY_LEFT_SHIFT    : return KEY_LEFT_SHIFT;
            case GLFW_KEY_LEFT_CONTROL  : return KEY_LEFT_CONTROL;
            case GLFW_KEY_LEFT_ALT      : return KEY_LEFT_ALT;
            case GLFW_KEY_RIGHT_SHIFT   : return KEY_RIGHT_SHIFT;
            case GLFW_KEY_RIGHT_CONTROL : return KEY_RIGHT_CONTROL;
            case GLFW_KEY_RIGHT_ALT     : return KEY_RIGHT_ALT;
            default:
            {
                std::cout << "Unknown Key: " << glfw_key << "\n";
                return KEY_NULL;
            }
        }
        return KEY_NULL;
    }

    static const char* get_helium_key_name(const Key key) {
        switch (key) {
            case KEY_SPACE         : return "SPACE";
            case KEY_APOSTROPHE    : return "'";
            case KEY_COMMA         : return ",";
            case KEY_MINUS         : return "-";
            case KEY_PERIOD        : return ".";
            case KEY_SLASH         : return "/";
            case KEY_0             : return "0";
            case KEY_1             : return "1";
            case KEY_2             : return "2";
            case KEY_3             : return "3";
            case KEY_4             : return "4";
            case KEY_5             : return "5";
            case KEY_6             : return "6";
            case KEY_7             : return "7";
            case KEY_8             : return "8";
            case KEY_9             : return "9";
            case KEY_SEMICOLON     : return ";";
            case KEY_EQUAL         : return "=";
            case KEY_A             : return "A";
            case KEY_B             : return "B";
            case KEY_C             : return "C";
            case KEY_D             : return "D";
            case KEY_E             : return "E";
            case KEY_F             : return "F";
            case KEY_G             : return "G";
            case KEY_H             : return "H";
            case KEY_I             : return "I";
            case KEY_J             : return "J";
            case KEY_K             : return "K";
            case KEY_L             : return "L";
            case KEY_M             : return "M";
            case KEY_N             : return "N";
            case KEY_O             : return "O";
            case KEY_P             : return "P";
            case KEY_Q             : return "Q";
            case KEY_R             : return "R";
            case KEY_S             : return "S";
            case KEY_T             : return "T";
            case KEY_U             : return "U";
            case KEY_V             : return "V";
            case KEY_W             : return "W";
            case KEY_X             : return "X";
            case KEY_Y             : return "Y";
            case KEY_Z             : return "Z";
            case KEY_LEFT_BRACKET  : return "{";
            case KEY_BACKSLASH     : return "\\";
            case KEY_RIGHT_BRACKET : return "}";
            case KEY_ACCENT        : return "`";
            case KEY_TILDE         : return "~";
            case KEY_ESCAPE        : return "ESCAPE";
            case KEY_ENTER         : return "ENTER";
            case KEY_TAB           : return "TAB";
            case KEY_BACKSPACE     : return "BACKSPACE";
            case KEY_INSERT        : return "INSERT";
            case KEY_DELETE        : return "DELETE";
            case KEY_RIGHT         : return "RIGHT ARROW";
            case KEY_LEFT          : return "LEFT ARROW";
            case KEY_DOWN          : return "DOWN ARROW";
            case KEY_UP            : return "UP ARROW";
            case KEY_PAGE_UP       : return "PAGE UP";
            case KEY_PAGE_DOWN     : return "PAGE DOWN";
            case KEY_HOME          : return "HOME";
            case KEY_END           : return "END";
            case KEY_CAPS_LOCK     : return "CAPS LOCK";
            case KEY_SCROLL_LOCK   : return "SCROLL LOCK";
            case KEY_NUM_LOCK      : return "NUM LOCK";
            case KEY_PRINT_SCREEN  : return "PRINT SCREEN";
            case KEY_PAUSE         : return "PAUSE";
            case KEY_F1            : return "F1";
            case KEY_F2            : return "F2";
            case KEY_F3            : return "F3";
            case KEY_F4            : return "F4";
            case KEY_F5            : return "F5";
            case KEY_F6            : return "F6";
            case KEY_F7            : return "F7";
            case KEY_F8            : return "F8";
            case KEY_F9            : return "F9";
            case KEY_F10           : return "F10";
            case KEY_F11           : return "F11";
            case KEY_F12           : return "F12";
            case KEY_KP_0          : return "0";
            case KEY_KP_1          : return "1";
            case KEY_KP_2          : return "2";
            case KEY_KP_3          : return "3";
            case KEY_KP_4          : return "4";
            case KEY_KP_5          : return "5";
            case KEY_KP_6          : return "6";
            case KEY_KP_7          : return "7";
            case KEY_KP_8          : return "8";
            case KEY_KP_9          : return "9";
            case KEY_KP_DECIMAL    : return ".";
            case KEY_KP_DIVIDE     : return "/";
            case KEY_KP_MULTIPLY   : return "*";
            case KEY_KP_SUBTRACT   : return "-";
            case KEY_KP_ADD        : return "+";
            case KEY_KP_ENTER      : return "ENTER";
            case KEY_KP_EQUAL      : return "=";
            case KEY_LEFT_SHIFT    : return "LEFT SHIFT";
            case KEY_LEFT_CONTROL  : return "LEFT CONTROL";
            case KEY_LEFT_ALT      : return "LEFT ALT";
            case KEY_RIGHT_SHIFT   : return "RIGHT SHIFT";
            case KEY_RIGHT_CONTROL : return "RIGHT CONTROL";
            case KEY_RIGHT_ALT     : return "RIGHT ALT";
            default                : return "UNKNOWN KEY";
        }
        return "UNKNOWN KEY";
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

        std::cout << InputManager::get_singleton().get_key_name(convert_glfw_key_to_helium_key(key)) << "\n";
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
        return std::string(get_helium_key_name(key));
    }
}