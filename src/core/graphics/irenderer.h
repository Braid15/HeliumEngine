#pragma once

#include <helium_std.h>
//#include "render_component.h"

namespace HeliumEngine {

    class ARenderComponent;

    class IRenderer {
    public:
        virtual void submit(ARenderComponent* render_component) = 0;
        virtual void render_begin() = 0;
        virtual void render_submissions() = 0;
        virtual void render_end() = 0;
        virtual bool initialize() = 0;
        virtual void shutdown() = 0;
        virtual ~IRenderer() {}
    };
}