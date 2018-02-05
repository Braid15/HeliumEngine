#pragma once

#include <helium_std.h>
#include "irenderer.h"
#include "simple_renderer_2d.h"
#include <deque>

namespace HeliumEngine {

    class SimpleRenderer2D : public IRenderer {
    private:
        std::deque<ARenderComponent*> _render_submissions; 
    public:
        SimpleRenderer2D() {}
        SimpleRenderer2D(const SimpleRenderer2D&) = delete;

        SimpleRenderer2D& operator=(const SimpleRenderer2D&) = delete;

        void submit(ARenderComponent* render_component) override;
        void render_begin() override;
        void render_submissions() override;
        void render_end() override;
        bool initialize() override;
        void shutdown() override;
    };
}