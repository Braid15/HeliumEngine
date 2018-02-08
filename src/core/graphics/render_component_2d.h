#pragma once

#include "render_component.h"
#include <core/math/math.h>
#include <core/_glfw_glew_include.h>
#include <core/utils/string_id.h>

namespace HeliumEngine {

    class RenderComponent2D : public ARenderComponent {
    private:
        enum { POS_VBO, COLOR_VBO };
        GLuint _vao;
        GLuint _vbo[2];
        GLuint _ibo;

        friend GameObject;
        static const StringId _component_type_id;
    public:
        RenderComponent2D() = delete;
        RenderComponent2D(const vec2 position, const vec2 size, const vec4 color, Shader* const shader);
        RenderComponent2D(const RenderComponent2D&) = delete;
        ~RenderComponent2D();

        RenderComponent2D& operator=(const RenderComponent2D&) = delete;

        void set_position(const vec2 position);
        void set_size(const vec2 size);
        void set_visible(const bool visible);

        const GLuint& get_vao_handle() const override;
        const GLuint& get_ibo_handle() const override;
        const RenderType get_render_type() const override;

        void on_render_begin() override;
        void on_render_end() override;

        bool initialize() override;
        void shutdown() override;
        void update() override {}
    };
}