#include "math.h"
#include <core/window_manager.h>

namespace HeliumEngine {

    vec2 pixel_point_to_gl_coordinate(const vec2& pixel_point) {
        vec2 gl_coordinate;
        gl_coordinate.x = (float)2.0 * pixel_point.x / WindowManager::get_singleton().get_width() - 1.0f;
        gl_coordinate.y = (float)-(2.0 * pixel_point.y / WindowManager::get_singleton().get_height() - 1.0f);
        return gl_coordinate;
    }
}