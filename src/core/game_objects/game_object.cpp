#include "game_object.h"
#include "icomponent.h"

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

    bool GameObject::initialize() {
        uint8 index = 0;
        uint8 components_initialized = 0;
        while (index < GAME_OBJECT_COMPONENT_MAX && components_initialized < _component_count) {
            if (_component_array[index]) {
                if (!_component_array[index]->initialize()) return false;
                components_initialized++;
            }
            index++;
        }

        return true;
    }

    void GameObject::shutdown() {
        // loop through everything just to be sure
        for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
            if (_component_array[i]) {
                _component_array[i]->shutdown();
                delete _component_array[i];
                _component_array[i] = nullptr;
            }
        }
    }

    void GameObject::update() {
        uint8 updated_components = 0;
        uint8 index = 0;
        // To make sure that all elements arent looped through unnecessarily
        while (index < GAME_OBJECT_COMPONENT_MAX && updated_components < _component_count) {
            if (_component_array[index]) {
                _component_array[index]->update();
                updated_components++;
            }
            index++;
        }
    }

    bool GameObject::attach_component(IComponent* component) {
        if (_component_count == GAME_OBJECT_COMPONENT_MAX) {
            #ifdef _DEBUG
            std::cout << "[GameObject] Component limit reached.\n";
            #endif
            return false;
        }

        // find first empty index
        for (uint8 i = 0; i < GAME_OBJECT_COMPONENT_MAX; i++) {
            if (!_component_array[i]) {
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

    GameObject::GameObject() {
        std::fill(_component_array, _component_array + GAME_OBJECT_COMPONENT_MAX, nullptr);
        _component_count = 0;
    }
}