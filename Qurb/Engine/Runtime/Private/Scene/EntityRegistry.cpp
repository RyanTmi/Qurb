#include "Scene/EntityRegistry.hpp"

#include "Scene/Entity.hpp"

namespace qurb
{
    auto EntityRegistry::createEntity() -> Entity
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

        return Entity(*this, entityId);
    }
}
