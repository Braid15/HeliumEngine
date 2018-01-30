#include "app_instance.h"


namespace HeliumEngine {

    GLFWwindow& AppInstance::get_window() const {
        assert(_window);
        return *_window;
    }

    bool AppInstance::initialize() {
        // Already initialized
        if (_window) return false;

        glfwInit();
        _window = glfwCreateWindow(1920, 1080, "AppInstance::_window", NULL, NULL);

        if (!_window) return false;

        glfwMakeContextCurrent(_window);

        glewExperimental = true;
        glewInit();

        return true;
    }

    void AppInstance::shutdown() {
        glfwTerminate();
        _window = nullptr;
    }

}