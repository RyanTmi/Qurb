/// \file Scene.hpp

#pragma once

#include "Containers/Vector.hpp"
#include "CoreDefines.hpp"
#include "Scene/Entity.hpp"
#include "Scene/EntityRegistry.hpp"

namespace qurb
{
    /// \brief The `Scene` class.
    class QURB_API Scene final
    {
    public:
        Scene() = default;

        Scene(const Scene&)                    = delete;
        auto operator=(const Scene&) -> Scene& = delete;

    public:
        auto createEntity() -> Entity;

        auto registry() -> EntityRegistry&;

        auto entities() -> Vector<Entity>&;

    private:
        friend class SceneRenderer;

    private:
        EntityRegistry _entityRegistry;
        Vector<Entity> _entities;
    };

    inline auto Scene::createEntity() -> Entity
    {
        const auto entity = _entityRegistry.createEntity();
        _entities.pushBack(entity);
        return entity;
    }

    inline auto Scene::registry() -> EntityRegistry&
    {
        return _entityRegistry;
    }

    inline auto Scene::entities() -> Vector<Entity>&
    {
        return _entities;
    }
}
