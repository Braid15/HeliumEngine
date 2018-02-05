#pragma once

#include <helium_std.h>
#include <core/_glfw_glew_include.h>
#include <core/math/math.h>
#include <core/shader.h>
#include <core/graphics/irenderer.h>

namespace HeliumEngine {

    typedef enum {
        RENDER_TYPE_2D,
        RENDER_TYPE_3D
    } RenderType;

    class ARenderComponent {
    protected:
        vec4 _color;
        vec4 _position;
        vec4 _size;
        Shader* _shader;
        bool _enabled;
        bool _visible;
        uint16 _index_count;
    public:
        ARenderComponent(const ARenderComponent&) = delete;
        virtual ~ARenderComponent();

        ARenderComponent& operator=(const ARenderComponent&) = delete;

        void set_color(const vec4 color);
        void set_color(const float32 r, const float32 g, const float32 b, const float32 a);
        const vec4& get_color() const;
        vec4& get_color();

        const vec4& get_position() const;
        const vec4& get_size() const;

        const uint16 get_index_count() const;

        void set_shader(Shader* const shader);
        Shader* get_shader();

        bool is_enabled() const;
        bool is_visible() const;

        // @TODO: Put vao and ibo in this class
        virtual const GLuint& get_vao_handle() const = 0;
        virtual const GLuint& get_ibo_handle() const = 0;
        virtual const RenderType get_render_type() const = 0;
        virtual void on_render_begin(IRenderer&  renderer) = 0;
        virtual void on_render(IRenderer& renderer) = 0;
        virtual void on_render_end(IRenderer& renderer) = 0;
    protected:
        ARenderComponent();
    };
}