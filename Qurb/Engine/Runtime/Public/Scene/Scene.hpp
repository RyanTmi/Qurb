#pragma once

#include "Containers/Vector.hpp"
#include "CoreDefines.hpp"
#include "Scene/Components.hpp"
#include "Scene/Entity.hpp"
#include "Scene/EntityRegistery.hpp"

namespace qurb
{
    // \brief The `Scene` class.
    class QURB_API Scene final
    {
    public:
        Scene();

        Scene(const Scene&)                    = delete;
        auto operator=(const Scene&) -> Scene& = delete;

    public:
        auto createEntity() -> Entity
        {
            auto entity = _entityRegistery.createEntity();
            _entities.pushBack(entity);
            return entity;
        }

        auto registery() -> EntityRegistery& { return _entityRegistery; }

        auto entities() -> Vector<Entity>& { return _entities; }

    private:
        friend class SceneRenderer;

    private:
        EntityRegistery _entityRegistery;
        Vector<Entity>  _entities;
    };

    inline Scene::Scene()
        : _entityRegistery()
        , _entities()
    {}
}
