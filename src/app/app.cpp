#include "app.h"

namespace HeliumEngine {

    AppInstance* App::_singleton = nullptr;

    void App::set_app_instance(AppInstance* const instance) {
        // Already initialized
        if (_singleton) return;

        _singleton = instance;
    }

    GLFWwindow& App::get_window() {
        assert(_singleton);

        return _singleton->get_window();
    }

}