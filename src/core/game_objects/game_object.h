#pragma once

#include <helium_std.h>
#include <core/utils/string_id.h>
#include "icomponent.h"

namespace HeliumEngine {

    class IComponent;
    #define GAME_OBJECT_COMPONENT_MAX 64

    // @TODO: Need unique id too
    class GameObject final {
    private:
        // @HANDLE
        // @TODO: Store collection of pointers to components,
        //        but eventually shjould use a handle to components.
        IComponent* _component_array[GAME_OBJECT_COMPONENT_MAX];
        uint8 _component_count;
    public:
        static GameObject* create();
        static GameObject* create(StringId game_object_id);

        GameObject(const GameObject&) = delete;
        GameObject& operator=(const GameObject&) = delete;

        bool initialize();
        void shutdown();
        // @OPTIMIZE
        // @TODO: This can be better since not every component needs to be updated, like render component
        void update();
        bool attach_component(IComponent* component);
        bool detach_component(StringId component_id);

        uint8 get_component_count() const;

        template <typename T>
        const T* const get_component(StringId component_id) {
            for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
                if (_component_array[i]->get_id() == component_id) {
                    return dynamic_cast<T*>(_component_array[i]);
                }
            }

            return nullptr;
        }


    private:
        GameObject();
    };
}