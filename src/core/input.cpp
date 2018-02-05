#include "input.h"

namespace HeliumEngine {

    KeyboardData::KeyboardData() {
        std::fill(keys, keys + KEY_LAST, KEY_STATE_RELEASED);
    }

    MouseData::MouseData() {
        std::fill(buttons, buttons + MOUSE_BUTTON_LAST, BUTTON_STATE_RELEASED);
        position.x = 0;
        position.y = 0;
    }

    JoystickData::JoystickData() {
        std::fill(buttons, buttons + JOYSTICK_BUTTON_LAST, BUTTON_STATE_RELEASED);
    }

}