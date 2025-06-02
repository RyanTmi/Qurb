#pragma once

#include "Containers/Vector.hpp"
#include "CoreDefines.hpp"
#include "CoreTypes.hpp"
#include "Debug/Exceptions.hpp"

#include <format>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace qurb
{
    class Entity;

    using EntityId = uint64;

    class ComponentPool
    {
    public:
        explicit ComponentPool(usize stride = 0)
            : _stride(stride)
        {}

    public:
        template <typename T, typename... Args>
        auto add(EntityId id, usize entityCount, Args&&... args) -> T&;

        template <typename T>
        auto at(uint64 index) -> T&;

        template <typename T>
        auto at(uint64 index) const -> const T&;

    private:
        usize         _stride;
        Vector<uint8> _data;
    };

    class QURB_API EntityRegistry
    {
    public:
        EntityRegistry() = default;

    public:
        auto createEntity() -> Entity;

        template <typename T, typename... Args>
        auto addComponent(EntityId id, Args&&... args) -> T&;

        template <typename T>
        auto getComponent(EntityId id) -> T&;

        template <typename... Ts>
        auto getComponents(EntityId id) -> std::tuple<Ts&...>;

        template <typename T>
        auto removeComponent(EntityId id) -> void;

        template <typename T>
        auto hasComponent(EntityId id) -> bool;

        template <typename... Ts>
        auto hasComponents(EntityId id) -> bool;

    private:
        class Component
        {
        public:
            template <typename T>
            static auto id() -> usize
            {
                static const usize id = _counter++;
                return id;
            }

        private:
            static inline usize _counter = 0;
        };

        friend class std::formatter<EntityRegistry>;

    private:
        Vector<ComponentPool>        _componentPools;  // One per component type.
        Vector<std::vector<bool>>    _entitiesMask;    // One per entity, each vector contains a mask for component presence.
        std::unordered_set<EntityId> _freeEntities;
    };

    //-----------------------------------------------------------------------------------------------------------------
    // class ComponentPool
    //-----------------------------------------------------------------------------------------------------------------

    template <typename T, typename... Args>
    auto ComponentPool::add(EntityId id, usize entityCount, Args&&... args) -> T&
    {
        if (_data.size() < entityCount * _stride)
        {
            _data.resize(entityCount * _stride);
        }

        // Here id should be less than entityCount.
        new (&_data[_stride * id]) T(std::forward<Args>(args)...);
        return at<T>(id);
    }

    template <typename T>
    auto ComponentPool::at(uint64 index) -> T&
    {
        auto& component = _data[index * _stride];
        return reinterpret_cast<T&>(component);
    }

    template <typename T>
    auto ComponentPool::at(uint64 index) const -> const T&
    {
        const auto& component = _data[index * _stride];
        return reinterpret_cast<const T&>(component);
    }

    //-----------------------------------------------------------------------------------------------------------------
    // class EntityRegistry
    //-----------------------------------------------------------------------------------------------------------------

    template <typename T, typename... Args>
    auto EntityRegistry::addComponent(EntityId id, Args&&... args) -> T&
    {
        const auto componentId = Component::id<T>();

        if (hasComponent<T>(id))
        {
            return _componentPools[componentId].template at<T>(id);
        }

        if (componentId >= _componentPools.size())
        {
            _componentPools.emplaceBack(sizeof(T));
        }

        if (componentId >= _entitiesMask[id].size())
        {
            _entitiesMask[id].resize(componentId + 1, false);
        }

        _entitiesMask[id][componentId] = true;
        return _componentPools[componentId].template add<T>(id, _entitiesMask.size(), std::forward<Args>(args)...);
    }

    template <typename T>
    auto EntityRegistry::getComponent(EntityId id) -> T&
    {
        const auto componentId = Component::id<T>();

        if (not hasComponent<T>(id))
        {
            throw Exception(std::format("Entity {} does not have the requested component {}.", id, typeid(T).name()));
        }

        return _componentPools[componentId].template at<T>(id);
    }

    template <typename... Ts>
    auto EntityRegistry::getComponents(EntityId id) -> std::tuple<Ts&...>
    {
        return std::tuple<Ts&...> {getComponent<Ts>(id)...};
    }

    template <typename T>
    auto EntityRegistry::removeComponent(EntityId id) -> void
    {
        const auto componentId = Component::id<T>();

        if (not hasComponent<T>(id))
        {
            return;
        }

        _entitiesMask[id][componentId] = false;
    }

    template <typename T>
    auto EntityRegistry::hasComponent(EntityId id) -> bool
    {
        const auto componentId = Component::id<T>();

        if (componentId >= _componentPools.size())
        {
            return false;
        }

        auto& entityMask = _entitiesMask[id];
        if (componentId >= entityMask.size())
        {
            entityMask.resize(componentId + 1, false);
        }

        return entityMask[componentId];
    }

    template <typename... Ts>
    auto EntityRegistry::hasComponents(EntityId id) -> bool
    {
        return (hasComponent<Ts>(id) && ...);
    }
}

template <>
struct std::formatter<qurb::EntityRegistry>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const qurb::EntityRegistry& r, FormatContext& ctx) const
    {
        auto out = ctx.out();
        out      = std::format_to(out, "EntityRegistry with {} component pools and {} entities", r._componentPools.size(), r._entitiesMask.size());
        return out;
    }
};
