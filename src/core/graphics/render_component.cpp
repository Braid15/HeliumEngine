#include "render_component.h"
#include <core/render_manager.h>

namespace HeliumEngine {

    ARenderComponent::~ARenderComponent() {
        if (_shader) {
            delete _shader;
        }
        _shader = nullptr;
        RenderManager::get_singleton().remove_render_component(this);
    }

    void ARenderComponent::set_color(const vec4 color) {
        _color = color;
    }

    void ARenderComponent::set_color(const float32 r, const float32 g, const float32 b, const float32 a) {
        _color.r = r;
        _color.g = g;
        _color.b = b;
        _color.a = a;
    }

    const vec4& ARenderComponent::get_color() const {
        return _color;
    }

    vec4& ARenderComponent::get_color() {
        return _color;
    }

    const vec4& ARenderComponent::get_position() const {
        return _position;
    }

    const vec4& ARenderComponent::get_size() const {
        return _size;
    }

    const uint16 ARenderComponent::get_index_count() const {
        return _index_count;
    }

    void ARenderComponent::set_shader(Shader* const shader) {
        if (_shader) {
            delete _shader;
        }
        _shader = shader;
    }

    Shader* ARenderComponent::get_shader() {
        return _shader;
    }

    bool ARenderComponent::is_enabled() const {
        return _enabled;
    }

    bool ARenderComponent::is_visible() const {
        return _visible;
    }

    ARenderComponent::ARenderComponent() {
        _shader      = nullptr;
        _enabled     = true;
        _index_count = 0;
        _visible     = true;

        RenderManager::get_singleton().add_render_component(this);
    }
}