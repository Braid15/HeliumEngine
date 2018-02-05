#include "window_manager.h"

namespace HeliumEngine {

    static void glfw_framebuffer_size_callback(GLFWwindow* window, int height, int width) {
        // Set width and height directly since set_width() and set_height resize the window
        WindowManager::get_singleton()._size.x = width;
        WindowManager::get_singleton()._size.y = height;
    }

    WindowManager WindowManager::_singleton;

    WindowManager& WindowManager::get_singleton() {
        return _singleton;
    }

    bool WindowManager::initialize() {
        // Already initialized
        if (_window) return false;

        _window = glfwCreateWindow(_size.x, _size.y, _title.c_str(), NULL, NULL);

        if (!_window) return false;

        glfwSetFramebufferSizeCallback(_window, glfw_framebuffer_size_callback);

        return true;
    }

    void WindowManager::shutdown() {
        glfwDestroyWindow(_window);
        _window = nullptr;
    }

    GLFWwindow& WindowManager::get_glfw_window() const {
        return *_window;
    }

    vec4& WindowManager::set_background_color(const vec4 color) {
        _background_color = color;
        return _background_color;
    }

    vec4& WindowManager::set_background_color(const float32 r, const float32 g, const float32 b, const float32 a) {
        _background_color.r = r;
        _background_color.g = g;
        _background_color.b = b;
        _background_color.a = a;
        return _background_color;
    }

    vec4 WindowManager::get_background_color() {
        return _background_color;
    }

    const vec4& WindowManager::get_background_color() const {
        return _background_color;
    }

    uvec2 WindowManager::set_size(const uint32 width, const uint32 height) {
        _size.x = width;
        _size.y = height;
        return _size;
    }

    uvec2 WindowManager::set_size(const uvec2 size) {
        _size = size;
        return _size;
    }

    uvec2 WindowManager::get_size() const {
        return _size;
    }

    uint32& WindowManager::set_height(const uint32 height) {
        _size.y = height;

        if (_window) {
            glfwSetWindowSize(_window, _size.x, _size.y);
        }

        return _size.y;
    }

    uint32 WindowManager::get_height() const {
        return _size.y;
    }

    uint32& WindowManager::set_width(const uint32 width) {
        _size.x = width;

        if (_window) {
            glfwSetWindowSize(_window, _size.x, _size.y);
        }

        return _size.x;
    }

    uint32 WindowManager::get_width() const {
        return _size.x;
    }

    std::string& WindowManager::set_title(const std::string title) {
        _title = title;

        if (_window) {
            glfwSetWindowTitle(_window, _title.c_str());
        }

        return _title;
    }

    const std::string& WindowManager::get_title() const {
        return _title;
    }

    WindowManager::WindowManager() {
        // Setting values to default. Ctor shouldn't do anything else
        _size.x = 1920;
        _size.y = 1080;

        _background_color.r = 0.2f;
        _background_color.g = 0.2f;
        _background_color.b = 0.2f;
        _background_color.a = 1.0f;

        _title = "WindowManager";
        _window = nullptr;
    }
}