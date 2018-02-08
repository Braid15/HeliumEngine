#pragma once

#include <helium_std.h>
#include <core/math/math.h>
#include <core/game_objects/icomponent.h>
#include <core/utils/string_id.h>

namespace HeliumEngine {

    class Transform : public BaseComponent {
    private:
        vec3 _position;
        vec3 _scale;
        vec4 _rotation;

        friend class GameObject;
        static const StringId _component_type_id;
    public:
        Transform();

        void set_position(const vec2 pos);
        void set_position(const vec3 pos);
        const vec3& get_position() const;
        vec3& get_position();

        void set_scale(const vec3 scale);
        const vec3& get_scale() const;
        vec3& get_scale();

        void set_rotation(const float32 angle, const vec3 rotation_axis);
        void set_rotation_angle(const float32 angle);
        const vec4& get_rotation() const;
        vec4& get_rotation();
        float32 get_rotation_angle();

        bool initialize() override;
        void shutdown() override;
        void update() override {}
    };
}
