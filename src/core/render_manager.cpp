#include "render_manager.h"

namespace HeliumEngine {

    RenderManager RenderManager::_singleton;

    RenderManager& RenderManager::get_singleton() {
        return _singleton;
    }

    bool RenderManager::initialize() {
        glGenBuffers(2, _primitive_batch_vbo);

        glBindBuffer(GL_ARRAY_BUFFER, _primitive_batch_vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_primitive_batch_vertices_buffer[0]), _primitive_batch_vertices_buffer[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, _primitive_batch_vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_primitive_batch_vertices_buffer[1]), _primitive_batch_vertices_buffer[1], GL_DYNAMIC_DRAW);

        return true;
    }

    void RenderManager::shutdown() {
        glDeleteBuffers(2, _primitive_batch_vbo);
    }

    void RenderManager::draw_line(uint32 start_x, uint32 start_y, uint32 end_x, uint32 end_y) {
        uint8 buffer = (_current_buffer == 0) ? 1 : 0;  
        _primitive_batch_vertices_buffer[buffer][_batch_count++] = start_x;
        _primitive_batch_vertices_buffer[buffer][_batch_count++] = start_y;
        _primitive_batch_vertices_buffer[buffer][_batch_count++] = end_x;
        _primitive_batch_vertices_buffer[buffer][_batch_count++] = end_y;
    }

    void RenderManager::render_batch() {

        glBindBuffer(GL_ARRAY_BUFFER, _primitive_batch_vbo[_current_buffer]);
        glDrawArrays(GL_LINES, 0, _batch_count / 2);

        _batch_count = 0;
        _current_buffer = (_current_buffer == 0) ? 1 : 0;
    }

    // Only initializes values. Ctor should not do anything else
    RenderManager::RenderManager() : _current_buffer(0), _batch_count(0)
    {}
}