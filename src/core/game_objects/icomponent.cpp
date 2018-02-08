#include "icomponent.h"

namespace HeliumEngine {

    BaseComponent::BaseComponent() {
        _owner    = nullptr;
        _enabled  = true;
    }

    const GameObject& BaseComponent::get_owner() const {
        assert(_owner);
        return *_owner;
    }

    GameObject& BaseComponent::get_owner() {
        assert(_owner);
        return *_owner;
    }

    const StringId BaseComponent::get_id() const {
        return _id;
    }

    bool BaseComponent::is_enabled() const {
        return _enabled;
    }

    void BaseComponent::set_enabled(const bool enabled) {
        _enabled = enabled;
    }

    void BaseComponent::set_id(const StringId id) {
        _id = id;
    }

    void BaseComponent::set_owner(const GameObject* const owner) {
        _owner = const_cast<GameObject*>(owner);
    }
}