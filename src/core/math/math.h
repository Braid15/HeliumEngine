#pragma once

#include <glm.hpp>
#include <type_ptr.hpp>
#include <matrix_transform.hpp>
#include <iostream>

namespace HeliumEngine {

    // @TODO: Just doing this out of laziness right now, but
    //        should implement wrapper or something
    using namespace glm;

    vec2 pixel_point_to_gl_coordinate(const vec2& pixel_point);

    inline std::ostream& operator<<(std::ostream& os, const vec2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const vec3& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const vec4& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return os;
    }
}