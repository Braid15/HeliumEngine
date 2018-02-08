#include "game_object.h"
#include "icomponent.h"
#include <core/transform.h>

namespace HeliumEngine {

    // @HANDLE
    // @TODO: Should return handle instead of raw ptr
    GameObject* GameObject::create() {
        return new GameObject();
    }

    GameObject* GameObject::create(StringId id) {
        std::cout << "[GameObject] UNIMPLEMENTD\n";
        return new GameObject();
    }

    GameObject::~GameObject() {
        if (_initialized) post_shutdown();
    }

    bool GameObject::is_enabled() const {
        return _enabled;
    }

    void GameObject::set_enabled(const bool enabled) {
        if (enabled == _enabled) return;

        _enabled        = enabled;
        uint8 index     = 0;
        uint8 component = 0;
        while (index < GAME_OBJECT_COMPONENT_MAX && component < _component_count) {
            if (_component_array[index]) {
                _component_array[index]->set_enabled(_enabled);
                component++;
            }
            index++;
        }
    }

    bool GameObject::initialize() {
        if (_initialized) return false;

        pre_initialize();

        on_initialize();

        uint8 index = 0;
        uint8 components_initialized = 0;
        while (index < GAME_OBJECT_COMPONENT_MAX && components_initialized < _component_count) {
            if (_component_array[index]) {
                if (!_component_array[index]->initialize()) return false;
                components_initialized++;
            }
            index++;
        }

        _initialized = true;

        on_start();

        return true;
    }

    void GameObject::shutdown() {
        if (!_initialized) return;
        on_shutdown();
        post_shutdown();
    }

    void GameObject::update() {
        if (!is_enabled()) return;

        on_update();

        uint8 updated_components = 0;
        uint8 index = 0;
        // To make sure that all elements arent looped through unnecessarily
        while (index < GAME_OBJECT_COMPONENT_MAX && updated_components < _component_count) {
            if (_component_array[index] && _component_array[index]->is_enabled()) {
                _component_array[index]->update();
                updated_components++;
            }
            index++;
        }
    }

    bool GameObject::attach_component(IComponent* component) {
        if (!component) return false;

        if (_component_count == GAME_OBJECT_COMPONENT_MAX) {
            #ifdef _DEBUG
            std::cout << "[GameObject] Component limit reached.\n";
            #endif
            return false;
        }

        // find first empty index
        for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
            if (!_component_array[i]) {
                // Don't add component that couldn't be initialized
                if (_initialized && !component->initialize()) {
                    #ifdef _DEBUG
                    std::cout << "[GameObject] Could not initialize component so it was not added.\n";
                    #endif
                    return false;
                }

                component->set_owner(this);
                _component_array[i] = component;
                _component_count++;

                return true;
            }
        }


        return false;
    }

    bool GameObject::detach_component(StringId component_id) {
        for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
            if (_component_array[i]->get_id() == component_id) {
                delete _component_array[i];
                _component_array[i] = nullptr;
                _component_count--;
                return true;
            }
        }

        return false;
    }

    uint8 GameObject::get_component_count() const {
        return _component_count;
    }

    void GameObject::post_shutdown() {
        for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
            if (_component_array[i]) {
                _component_array[i]->shutdown();
                delete _component_array[i];
                _component_array[i] = nullptr;
            }
        }

        _initialized = false;
    }

    void GameObject::pre_initialize() {
        std::fill(_component_array, _component_array + GAME_OBJECT_COMPONENT_MAX, nullptr);
        _component_count = 0;
        _enabled         = true;
        _initialized     = false;

        // Every GameObject should have a transform
        attach_component(new Transform());
    }
}