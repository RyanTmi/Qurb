/// \file Entity.hpp

#pragma once

#include "CoreDefines.hpp"
#include "Scene/EntityRegistery.hpp"

#include <limits>
#include <tuple>

namespace qurb
{
    // \brief The `Entity` class.
    class QURB_API Entity final
    {
    public:
        Entity(EntityId id, EntityRegistery& registery);

    public:
        [[nodiscard]] auto id() const -> EntityId { return _id; }

        template <typename T, typename... Args>
        auto addComponent(Args&&... args) -> T&;

        template <typename T>
        auto getComponent() -> T&;

        template <typename... Ts>
        auto getComponents() -> std::tuple<Ts&...>;

        template <typename T>
        auto hasComponent() -> bool;

        template <typename... Ts>
        auto hasComponents() -> bool;

        template <typename T>
        auto removeComponent() -> void;

    private:
        EntityId         _id;
        EntityRegistery& _registery;
    };

    constexpr auto invalidEntityId = std::numeric_limits<EntityId>::max();

    inline Entity::Entity(EntityId id, EntityRegistery& registery)
        : _id(id)
        , _registery(registery)
    {}

    template <typename T, typename... Args>
    auto Entity::addComponent(Args&&... args) -> T&
    {
        return _registery.addComponent<T>(_id, std::forward<Args>(args)...);
    }

    template <typename T>
    auto Entity::getComponent() -> T&
    {
        return _registery.getComponent<T>(_id);
    }

    template <typename... Ts>
    auto Entity::getComponents() -> std::tuple<Ts&...>
    {
        return _registery.getComponents<Ts...>(_id);
    }

    template <typename T>
    auto Entity::hasComponent() -> bool
    {
        return _registery.hasComponent<T>(_id);
    }

    template <typename... Ts>
    auto Entity::hasComponents() -> bool
    {
        return _registery.hasComponents<Ts...>(_id);
    }

    template <typename T>
    auto Entity::removeComponent() -> void
    {
        return _registery.removeComponent<T>(_id);
    }
}
