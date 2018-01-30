#pragma once

#include <helium_std.h>

#include "app_instance.h"
#include <glfw3.h>

namespace HeliumEngine {

    class App final {
    private:
        static AppInstance* _singleton;
    public:
        App() {}
        App(const App&) = delete;
        ~App() {}
    public:
        static void set_app_instance(AppInstance* const instance);
        static GLFWwindow& get_window();
    public:
        App& operator=(const App&) = delete;
    };
}