#pragma once

#include <helium_std.h>
#include <core/utils/string_id.h>
#include "icomponent.h"

namespace HeliumEngine {

    class IComponent;
    #define GAME_OBJECT_COMPONENT_MAX 64

    // @TODO: Need unique id too
    class GameObject {
    private:
        // @HANDLE
        // @TODO: Store collection of pointers to components,
        //        but eventually shjould use a handle to components.
        IComponent* _component_array[GAME_OBJECT_COMPONENT_MAX];
        uint8 _component_count;
        bool _enabled;
        bool _initialized;
    public:
        static GameObject* create();
        static GameObject* create(StringId game_object_id);

        template <typename T>
        static T* create() {
            return new T();
        }

        GameObject(const GameObject&) = delete;
        GameObject& operator=(const GameObject&) = delete;
        virtual ~GameObject();

        bool is_enabled() const;
        void set_enabled(const bool enabled);

        bool initialize();
        void shutdown();
        // @OPTIMIZE
        // @TODO: This can be better since not every component needs to be updated, like render component
        // @TODO: Update should be private so that only GameObjectManager can call it and it can control update order.
        //        User updates will be called in virtual protected methods;
        void update();
        bool attach_component(IComponent* component);

        template <typename T>
        bool attach_component() {

        }

        bool detach_component(StringId component_id);

        uint8 get_component_count() const;

        template <typename T>
        T* const get_component() {
            for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
                if (_component_array[i]->get_id() == T::_component_type_id) {
                    return dynamic_cast<T*>(_component_array[i]);
                }
            }

            return nullptr;
        }

    protected:
        // For derived classes. Called before components are initialized.
        virtual void on_initialize() {}

        // For derived classes. Called after all components have been initialized.
        virtual void on_start() {}

        // For derived classes. Called before components have been updated.
        virtual void on_update() {}

        // For derived classes. Called on shutdown. Components still exist at this point.
        virtual void on_shutdown() {}
    protected:
        GameObject() {}

        void post_shutdown();
        void pre_initialize();
    };
}
