#pragma once

#include <cstdint>
#include <iostream>

namespace HeliumEngine {

    typedef uint8_t  uint8;
    typedef uint16_t uint16;
    typedef uint32_t uint32;
    typedef uint64_t uint64;

    typedef int8_t  int8;
    typedef int16_t int16;
    typedef int32_t int32;
    typedef int64_t int64;

    typedef unsigned char byte;

    typedef char16_t char16;
    typedef char32_t char32;

    typedef float  float32;
    typedef double float64;

    inline std::ostream& operator<<(std::ostream& os, const uint8& val) {
        os << static_cast<int>(val);
        return os;
    }
}