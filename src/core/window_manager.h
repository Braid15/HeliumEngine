#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "math/math.h"

namespace HeliumEngine {

    class WindowManager final {
    private:
        friend class Engine;

        static WindowManager _singleton;

        GLFWwindow* _window;
        uvec2 _size;
        std::string _title;
        vec4 _background_color;

        friend void glfw_framebuffer_size_callback(GLFWwindow* window, int height, int width);

    public:
        WindowManager(const WindowManager&) = delete;
        ~WindowManager() {}

        WindowManager& operator=(const WindowManager&) = delete;

        static WindowManager& get_singleton();

        GLFWwindow& get_glfw_window() const;

        vec4& set_background_color(const vec4 color);
        vec4& set_background_color(const float32 r, const float32 g, const float32 b, const float32 a=1.0f);
        vec4 get_background_color();
        const vec4& get_background_color() const;

        uvec2 set_size(const uint32 width, const uint32 height);
        uvec2 set_size(const uvec2 size);
        uvec2 get_size() const;

        uint32& set_height(const uint32 height);
        uint32 get_height() const;

        uint32& set_width(const uint32 width);
        uint32 get_width() const;

        std::string& set_title(const std::string title);
        const std::string& get_title() const;

    private:
        WindowManager();

        bool initialize();
        void shutdown();
    };
}