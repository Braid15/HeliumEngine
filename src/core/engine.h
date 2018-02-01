#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "window_manager.h"

namespace HeliumEngine {
    // @TODO: See below to see what else needs implementing
    // http://www.glfw.org/docs/latest/window_guide.html#window_hints

    // Engine controls mainloop and initializes all of the managers.
    // It will take in a reference to some class that will contain the game logic
    // and it will run it. 
    // @TODO: The idea is to make the engine a dll so that apps can change
    class Engine final {
    private:
        static Engine _singleton;
        WindowManager* _window_manager;

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
    private:
        Engine();

        bool initialize();
        void shutdown();

        void process_input();
        void update();
        void render();

        int get_exit_code() const;
    };
}