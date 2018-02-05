#include "transform.h"

namespace HeliumEngine {

    Transform::Transform() {
        _position = vec3(0.0f, 0.0f, 0.0f);
        _scale    = vec3(1.0f, 1.0f, 1.0f);
        _rotation = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    void Transform::set_position(const vec3 pos) {
        _position = pos;
    }

    const vec3& Transform::get_position() const {
        return _position;
    }

    vec3& Transform::get_position() {
        return _position;
    }

    void Transform::set_scale(const vec3 scale) {
        _scale = scale;
    }

    const vec3& Transform::get_scale() const {
        return _scale;
    }

    vec3& Transform::get_scale() {
        return _scale;
    }

    void Transform::set_rotation(const float32 angle, const vec3 rotation_axis) {
        _rotation = vec4(rotation_axis, angle);
    }

    void Transform::set_rotation_angle(const float32 angle) {
        _rotation.w = angle;
    }

    const vec4& Transform::get_rotation() const {
        return _rotation;
    }

    vec4& Transform::get_rotation() {
        return _rotation;
    }

    float32 Transform::get_rotation_angle() {
        return _rotation.w;
    }
}