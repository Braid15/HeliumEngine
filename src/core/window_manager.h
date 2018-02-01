#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"

namespace HeliumEngine {

    class WindowManager final {
    private:
        static WindowManager _singleton;

        GLFWwindow* _window;

        uint32 _height;
        uint32 _width;

        std::string _title;

        friend void glfw_framebuffer_size_callback(GLFWwindow* window, int height, int width);

    public:
        WindowManager(const WindowManager&) = delete;
        ~WindowManager() {}

        WindowManager& operator=(const WindowManager&) = delete;

        static WindowManager& get_singleton();

        bool initialize();
        void shutdown();
        GLFWwindow& get_glfw_window() const;

        uint32& set_height(uint32 height);
        uint32 get_height() const;

        uint32& set_width(uint32 width);
        uint32 get_width() const;

        std::string& set_title(std::string title);
        const std::string& get_title() const;

    private:
        WindowManager();
    };
}