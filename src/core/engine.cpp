#include "engine.h"
#include <core/math/math.h>
#include <core/graphics/render_component.h>
#include <core/graphics/render_component_2d.h>

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
        _input_manager  = nullptr;
        _render_manager = nullptr;
        _vsync          = true;
    }

    bool Engine::initialize() {
        _exit_code = -1;

        glfwInit();

        _window_manager = &WindowManager::get_singleton();
        if (!_window_manager->initialize()) return false;

        // Do this stuff before initializing any other manager
        glfwMakeContextCurrent(&_window_manager->get_glfw_window());
        glewExperimental = true;
        glewInit();

        _input_manager = &InputManager::get_singleton();
        if (!_input_manager->initialize()) return false;

        _render_manager = &RenderManager::get_singleton();
        if (!_render_manager->initialize()) return false;

        if (_vsync) {
            glfwSwapInterval(1);
        }

        assert(_application);
        if (!_application->initialize()) return false;

        _exit_code = 0;


        return true;
    }

    void Engine::shutdown() {
        // Order is important here!! Should be opposite to init order in Engine::initialize()
        assert(_application);
        _application->shutdown();

        assert(_render_manager);
        _render_manager->shutdown();

        assert(_input_manager);
        _input_manager->shutdown();

        assert(_window_manager);
        _window_manager->shutdown();
    }

    void Engine::process_input() {
        assert(_application);
        InputData data(_input_manager->get_keyboard_data(),
                       _input_manager->get_mouse_data(),
                       _input_manager->get_joystick_data());
        _application->handle_input(data);
    }

    void Engine::render() {
        assert(_render_manager);
        _render_manager->render_begin();
        _render_manager->render();
        _render_manager->render_end();
        _render_manager->render_present();
    }

    void Engine::update() {
        assert(_application);
        _application->update();
    }

    void Engine::set_application(GameApp* app) {
        _application = app;
    }

    int Engine::get_exit_code() const {
        return _exit_code;
    }
}