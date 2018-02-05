#pragma once

#include <glm.hpp>
#include <type_ptr.hpp>
#include <matrix_transform.hpp>

namespace HeliumEngine {

    // @TODO: Just doing this out of laziness right now, but
    //        should implement wrapper or something
    using namespace glm;

    vec2 pixel_point_to_gl_coordinate(const vec2& pixel_point);
}