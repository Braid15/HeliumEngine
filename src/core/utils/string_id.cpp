#include "string_id.h"
#include "hash.h"


namespace HeliumEngine {

    StringIdManager StringIdManager::_singleton;

    StringIdManager& StringIdManager::get_singleton() {
        return _singleton;
    }

    StringId StringIdManager::intern_string(const char* str) {
        assert(_hash);
        StringId id = _hash->hash_u32(str);

        std::map<StringId, const char*>::iterator iter = _string_id_map.find(id);

        if (iter == _string_id_map.end()) {
            _string_id_map[id] = _strdup(str);
        }

        return id;
    }

    const char* StringIdManager::find_string(StringId id) const {
        std::map<StringId, const char*>::const_iterator iter = _string_id_map.find(id);

        if (iter == _string_id_map.end()) return "";

        return iter->second;
    }

    void StringIdManager::set_hash_function(IHashFunction* hash_func) {
        if (_hash) delete _hash;
        _hash = hash_func;
    }

    bool StringIdManager::initialize() {
        // Need to register known strings
        return true;
    }

    void StringIdManager::shutdown() {
        std::map<StringId, const char*>::iterator iter = _string_id_map.begin();
        std::map<StringId, const char*>::iterator end  = _string_id_map.end();

        while (iter != end) {
            if (iter->second) {
                free((void*)iter->second);
                iter->second = nullptr;
            }
            _string_id_map.erase(iter++);
        }

        if (_hash) {
            delete _hash;
            _hash = nullptr;
        }
    }
}