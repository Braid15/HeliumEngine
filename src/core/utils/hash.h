#pragma once

#include <helium_std.h>

namespace HeliumEngine {

    class IHashFunction {
    public:
        virtual uint32 hash_u32(const char* str) const = 0;
        virtual uint64 hash_u64(const char* str) const = 0;
        virtual ~IHashFunction() {}
    };

    class StdHashFunction : public IHashFunction {
    public:
        StdHashFunction() = default;
        StdHashFunction(const StdHashFunction&) = delete;
        StdHashFunction& operator=(const StdHashFunction&) = delete;

        uint32 hash_u32(const char* str) const override;
        uint64 hash_u64(const char* str) const override;
    };
}