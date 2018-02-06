#pragma once

#include <helium_std.h>

namespace HeliumEngine {

    typedef uint32 StringId;

    class IHashFunction;

    class StringIdManager final {
    private:
        friend class Engine;

        static StringIdManager _singleton;

        std::map<StringId, const char*> _string_id_map;
        IHashFunction* _hash;
    public:
        StringIdManager(const StringIdManager&) = delete;
        StringIdManager& operator=(const StringIdManager&) = delete;

        static StringIdManager& get_singleton();

        StringId intern_string(const char* str);
        const char* find_string(StringId id) const;

        void set_hash_function(IHashFunction* hash_func);
    private:
        StringIdManager() = default;

        bool initialize();
        void shutdown();
    };

    #define STRING_ID(str) StringIdManager::get_singleton().intern_string((str))
}