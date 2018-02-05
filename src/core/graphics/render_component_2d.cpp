#include "render_component_2d.h"

namespace HeliumEngine {

    RenderComponent2D::RenderComponent2D(const vec2 position, const vec2 size, const vec4 color, Shader* const shader) : 
        ARenderComponent() {

        _position = vec4(position, 1.0, 1.0);
        _size     = vec4(size, 0.0, 1.0);
        _color    = color;
        _shader   = shader;

        if (!_shader->compile()) {
            std::cout << _shader->get_error_string() << "\n";
        }

        glGenVertexArrays(1, &_vao);
        glGenBuffers(2, _vbo);
        glGenBuffers(1, &_ibo);

        glBindVertexArray(_vao);

        float32 vertices[]  = {
            0.0f,   0.0f,   0.0f,
            0.0f,   size.y, 0.0f,
            size.x, size.y, 0.0f,
            size.x, 0.0f,   0.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, _vbo[POS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        float32 color_array[] = {
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a,
            color.r, color.g, color.b, color.a,
        };

        glBindBuffer(GL_ARRAY_BUFFER, _vbo[COLOR_VBO]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
        _index_count = 6;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    RenderComponent2D::~RenderComponent2D() {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(3, _vbo);
        glDeleteBuffers(1, &_ibo);
    }

    void RenderComponent2D::set_position(const vec2 position) {
        if (is_visible()) {
            _position = vec4(position, 1.0, 1.0);
        } else {
            _position = vec4(position, 0.0, 1.0);
        }
    }

    void RenderComponent2D::set_size(const vec2 size) {
        _size = vec4(size, 0.0, 1.0);
    }

    void RenderComponent2D::set_visible(const bool visible) {
        if (visible) {
            _position.z = 1.0;
            _visible    = true;
        } else {
            _position.z = 0.0;
            _visible    = false;
        }
    }

    const GLuint& RenderComponent2D::get_vao_handle() const {
        return _vao;
    }

    const GLuint& RenderComponent2D::get_ibo_handle() const {
        return _ibo;
    }

    const RenderType RenderComponent2D::get_render_type() const {
        return RENDER_TYPE_2D;
    }

    void RenderComponent2D::on_render_begin(IRenderer& renderer) {
        if (is_visible()) {
            renderer.submit(this);
        }
    }

    void RenderComponent2D::on_render(IRenderer& renderer) {

    }

    void RenderComponent2D::on_render_end(IRenderer& renderer) {

    }
}