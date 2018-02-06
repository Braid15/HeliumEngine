#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "window_manager.h"
#include "input_manager.h"
#include "render_manager.h"
#include <app/game_app.h>
#include "timer.h"
#include <core/utils/string_id.h>

namespace HeliumEngine {
    // @TODO: See below to see what else needs implementing
    // http://www.glfw.org/docs/latest/window_guide.html#window_hints

    // Engine controls mainloop and initializes all of the managers.
    // It will take in a reference to some class that will contain the game logic
    // and it will run it. 
    // @TODO: The idea is to make the engine a dll so that apps can change
    class Engine final {
    private:
        friend class Application;

        static Engine _singleton;

        WindowManager* _window_manager;
        InputManager* _input_manager;
        RenderManager* _render_manager;
        StringIdManager* _string_id_manager;

        GameApp* _application;


        int8 _exit_code;
        uint8 _fps;

        // @TODO: I don't know if this should be in this class
        bool _vsync;
    public:
        Engine(const Engine&) = delete;
        ~Engine() {}

        Engine& operator=(const Engine&) = delete;

        static Engine& get_singleton();
        static int run();
        float32 get_delta_time();
    private:
        Engine();

        bool initialize();
        void shutdown();

        void process_input();
        void update();
        void render();

        void set_application(GameApp* app);

        int get_exit_code() const;
    };
}