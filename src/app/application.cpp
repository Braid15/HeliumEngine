#include "application.h"
#include <core/engine.h>

namespace HeliumEngine {

    GameApp* Application::_app  = nullptr;
    int Application::_exit_code = 0;

    void Application::start(GameApp* app) {
        _app = app;
       Engine::get_singleton().set_application(_app);
        _exit_code = Engine::run();
        delete _app;
    }

    int Application::get_exit_code() {
        return _exit_code;
    }
}