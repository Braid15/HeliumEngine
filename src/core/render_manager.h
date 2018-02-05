#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"
#include "graphics/irenderer.h"
#include "graphics/render_component.h"
#include "graphics/render_component_2d.h"

namespace HeliumEngine {

    class RenderManager final {
    private:
        friend class Engine;
        // @TEMP: Doing this until messages are implemented
        friend class ARenderComponent;

        static RenderManager _singleton;

        // @TEMP: SHould choose better data structure or use handles for RenderCOmponents or seomthing
        std::list<ARenderComponent*> _render_components;

        IRenderer* _renderer;
    public:
        RenderManager(const RenderManager&) = delete;
        ~RenderManager() {}

        RenderManager& operator=(const RenderManager&) = delete;

        static RenderManager& get_singleton();

        void submit(ARenderComponent* render_component);

        // @TEMP: Should this be in another class?
        void draw_line(uint32 start_x, uint32 start_y, uint32 end_x, uint32 end_y);

    private:
        RenderManager();

        bool initialize();
        void shutdown();

        void add_render_component(ARenderComponent* const component);
        void remove_render_component(ARenderComponent* const component);

        void set_renderer(IRenderer* renderer);

        void render_begin();
        void render();
        void render_end();
        void render_present();
    };
}