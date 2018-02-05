#pragma once

#include <helium_std.h>
#include "game_app.h"

namespace HeliumEngine {

    class Application final {
    private:
        static GameApp* _app;
        static int _exit_code;
    public:
        Application() = delete;
        Application(const Application&) = delete;
        ~Application() {}
        Application& operator=(const Application&) = delete;

        static void start(GameApp* app);
        static int get_exit_code();
    };
}