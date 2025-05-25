#include "Scene/EntityRegistery.hpp"

#include "Scene/Entity.hpp"

namespace qurb
{
    auto EntityRegistery::createEntity() -> Entity
    {
        auto entityId = invalidEntityId;

        if (_freeEntities.empty())
        {
            _entitiesMask.emplaceBack();
            entityId = _entitiesMask.size() - 1;
        }
        else
        {
            entityId = *_freeEntities.begin();
            _freeEntities.erase(entityId);
        }

        return Entity(entityId, *this);
    }
}
