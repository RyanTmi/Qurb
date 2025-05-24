#pragma once

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
        auto registery() -> EntityRegistery& { return _entityRegistery; }

    private:
        EntityRegistery _entityRegistery;
    };
}
