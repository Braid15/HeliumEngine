#include "window_manager.h"

namespace HeliumEngine {

    static void glfw_framebuffer_size_callback(GLFWwindow* window, int height, int width) {
        // Set width and height directly since set_width() and set_height resize the window
        WindowManager::get_singleton()._height = height;
        WindowManager::get_singleton()._width  = width;
    }

    WindowManager WindowManager::_singleton;

    WindowManager& WindowManager::get_singleton() {
        return _singleton;
    }

    bool WindowManager::initialize() {
        // Already initialized
        if (_window) return false;

        _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

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

    uint32& WindowManager::set_height(uint32 height) {
        _height = height;

        if (_window) {
            glfwSetWindowSize(_window, _height, _width);
        }

        return _height;
    }

    uint32 WindowManager::get_height() const {
        return _height;
    }

    uint32& WindowManager::set_width(uint32 width) {
        _width = width;

        if (_window) {
            glfwSetWindowSize(_window, _height, _width);
        }

        return _width;
    }

    uint32 WindowManager::get_width() const {
        return _width;
    }

    std::string& WindowManager::set_title(std::string title) {
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
        _height = 1080;
        _width  = 1920;
        _title  = "WindowManager";
        _window = nullptr;
    }
}