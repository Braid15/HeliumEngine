#pragma once

#include <helium_std.h>
#include <core/utils/string_id.h>

namespace HeliumEngine {

    //
    // Any components must define a static StringId named _component_type_id
    //

    class GameObject;

    class IComponent {
    public:
        virtual const GameObject& get_owner() const = 0;
        virtual GameObject& get_owner() = 0;
        virtual const StringId get_id() const = 0;
        virtual bool initialize() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;
        virtual bool is_enabled() const = 0;
        virtual void set_enabled(const bool disabled) = 0;
        virtual ~IComponent() {}
    protected:
        friend class GameObject;
        virtual void set_owner(const GameObject* const owner) = 0;
    };

    class BaseComponent : public IComponent {
    private:
        GameObject* _owner;
        StringId _id;
        bool _enabled;
    public:
        BaseComponent();
        virtual ~BaseComponent() {}
        const GameObject& get_owner() const override;
        GameObject& get_owner() override;
        const StringId get_id() const override;

        bool is_enabled() const override;
        void set_enabled(const bool enabled) override;

        virtual bool initialize() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;
    protected:
        friend class GameObject;
        void set_id(const StringId id);
        void set_owner(const GameObject* const owner) override;
    };
}