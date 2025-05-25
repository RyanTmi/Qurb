#pragma once

#include "Containers/Vector.hpp"
#include "Scene/Entity.hpp"
#include "Scene/EntityRegistery.hpp"

namespace qurb
{
    // \brief The `Scene` class.
    class Scene final
    {
    public:
        Scene() = default;

        Scene(const Scene&)                    = delete;
        Scene(Scene&&)                         = delete;
        auto operator=(const Scene&) -> Scene& = delete;
        auto operator=(Scene&&) -> Scene&      = delete;

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
        EntityRegistery _entityRegistery;
        Vector<Entity>  _entities;
    };
}
