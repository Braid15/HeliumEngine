#include "engine.h"

namespace HeliumEngine {

    Engine Engine::_singleton;

    Engine& Engine::get_singleton() {
        return _singleton;
    }

    int Engine::run() {
       if (!_singleton.initialize()) return _singleton.get_exit_code();

       // @TEMP: Experimenting. Once settled on implementation,
       //        factor to seperate methods or class.
       //        https://gafferongames.com/post/fix_your_timestep/
       float64 t  = 0.0;
       float64 dt = 0.01;
       //float64 current_time = static_cast<float64>(glfwGetTimerValue());
       float64 current_time = glfwGetTime();
       float64 accumulator = 0.0;

       while (!glfwWindowShouldClose(&_singleton._window_manager->get_glfw_window())) {
           float64 new_time = glfwGetTime();
           float64 frame_time = new_time - current_time;
           if (frame_time > 0.25) {
               frame_time = 0.25;
           }

           //std::cout << "accumulator: " << accumulator << "\n";
           current_time = new_time;
           accumulator += frame_time;

           while (accumulator >= dt) {
               _singleton.process_input();
               _singleton.update();
               t += dt;
               accumulator -= dt;
           }

           const float64 alpha = accumulator / dt;
            
           _singleton.render();
            
           glfwPollEvents();
       }

       _singleton.shutdown();
       glfwTerminate();

       return _singleton.get_exit_code();
    }

    Engine::Engine() {
        // Setting fields to default. Ctor should not be used for anything else.
        _exit_code      = 0;
        _window_manager = nullptr;
        _vsync          = true;
    }

    bool Engine::initialize() {
        _exit_code = -1;

        glfwInit();

        _window_manager = &WindowManager::get_singleton();

        if (!_window_manager->initialize()) return false;

        glfwMakeContextCurrent(&_window_manager->get_glfw_window());

        glewExperimental = true;
        glewInit();

        if (_vsync) {
            glfwSwapInterval(1);
        }

        _exit_code = 0;
        return true;
    }

    void Engine::shutdown() {
        assert(_window_manager);
        _window_manager->shutdown();
    }

    void Engine::process_input() {

    }

    void Engine::update() {
    }

    void Engine::render() {
       glClearColor(0.2, 0.2, 0.2, 1.0);
       glClear(GL_COLOR_BUFFER_BIT);
       glfwSwapBuffers(&_window_manager->get_glfw_window());
    }

    int Engine::get_exit_code() const {
        return _exit_code;
    }
}