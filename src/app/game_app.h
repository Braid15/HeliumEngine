#pragma once

#include <helium_std.h>
#include <core/input.h>

namespace HeliumEngine {

    class GameApp {
    private:
    public:
        virtual bool initialize();
        virtual void shutdown();
        virtual void handle_input(InputData& input);
        virtual void update();
    };
}