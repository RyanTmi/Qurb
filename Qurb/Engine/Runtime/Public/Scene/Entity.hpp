/// \file Entity.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Scene/EntityRegistry.hpp"

#include <limits>
#include <tuple>

namespace qurb
{
    constexpr auto invalidEntityId = std::numeric_limits<EntityId>::max();

    /// \brief The `Entity` class.
    class QURB_API Entity final
    {
    public:
        explicit Entity(EntityRegistry& registry, EntityId id = invalidEntityId);

    public:
        [[nodiscard]] auto id() const -> EntityId { return _id; }

        template <typename T, typename... Args>
        auto addComponent(Args&&... args) -> T&;

        template <typename T>
        auto getComponent() -> T&;

        template <typename... Ts>
        auto getComponents() -> std::tuple<Ts&...>;

        template <typename T>
        [[nodiscard]] auto hasComponent() const -> bool;

        template <typename... Ts>
        [[nodiscard]] auto hasComponents() const -> bool;

        template <typename T>
        auto removeComponent() const -> void;

    private:
        EntityRegistry& _registry;
        EntityId         _id;
    };

    inline Entity::Entity(EntityRegistry& registry, EntityId id)
        : _registry(registry)
        , _id(id)
    {}

    template <typename T, typename... Args>
    auto Entity::addComponent(Args&&... args) -> T&
    {
        return _registry.addComponent<T>(_id, std::forward<Args>(args)...);
    }

    template <typename T>
    auto Entity::getComponent() -> T&
    {
        return _registry.getComponent<T>(_id);
    }

    template <typename... Ts>
    auto Entity::getComponents() -> std::tuple<Ts&...>
    {
        return _registry.getComponents<Ts...>(_id);
    }

    template <typename T>
    auto Entity::hasComponent() const -> bool
    {
        return _registry.hasComponent<T>(_id);
    }

    template <typename... Ts>
    auto Entity::hasComponents() const -> bool
    {
        return _registry.hasComponents<Ts...>(_id);
    }

    template <typename T>
    auto Entity::removeComponent() const -> void
    {
        return _registry.removeComponent<T>(_id);
    }
}
