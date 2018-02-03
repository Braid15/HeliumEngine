#pragma once

#include <helium_std.h>
#include "_glfw_glew_include.h"

namespace HeliumEngine {

    #define MAX_BATCH_SIZE 1000

    class RenderManager final {
    private:
        static RenderManager _singleton;

        GLuint _primitive_batch_vbo[2];

        uint32 _batch_count;
        uint8 _current_buffer;
        uint32 _primitive_batch_vertices_buffer[2][MAX_BATCH_SIZE];
    public:
        RenderManager(const RenderManager&) = delete;
        ~RenderManager() {}

        RenderManager& operator=(const RenderManager&) = delete;

        static RenderManager& get_singleton();

        bool initialize();
        void shutdown();

        // @TEMP: Should this be in another class?
        void draw_line(uint32 start_x, uint32 start_y, uint32 end_x, uint32 end_y);

        // @TEMP: This should only be exposed to Engine
        void render_batch();
    private:
        RenderManager();
    };
}