#include "hash.h"

namespace HeliumEngine {

    uint32 StdHashFunction::hash_u32(const char* str) const {
        return static_cast<uint32>(std::hash<std::string>{}(str));
    }

    uint64 StdHashFunction::hash_u64(const char* str) const {
        return static_cast<uint64>(std::hash<std::string>{}(str));
    }
}