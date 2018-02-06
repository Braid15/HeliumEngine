#pragma once

#include <helium_std.h>
#include <core/utils/string_id.h>

namespace HeliumEngine {

    class GameObject;

    class IComponent {
    public:
        virtual const GameObject& get_owner() const = 0;
        virtual GameObject& get_owner() = 0;
        virtual StringId get_id() = 0;
        virtual bool initialize() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;
        virtual ~IComponent() {}
    private:
        friend class GameObject;
        virtual void set_owner(const GameObject* const owner) = 0;
    };
}