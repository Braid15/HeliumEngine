#pragma once

#include <helium_std.h>

#include <glew.h>
#include <glfw3.h>

namespace HeliumEngine {

    class AppInstance final {
    private:
        GLFWwindow* _window;
    public:
        AppInstance() {}
        AppInstance(const AppInstance&) = delete;
        ~AppInstance() {}
    public:
        GLFWwindow& get_window() const;
        bool initialize();
        void shutdown();
    public:
        AppInstance& operator=(const AppInstance&) = delete;
    };
}
