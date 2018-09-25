#include <list>
#include "EntityComponentManager.h"

EntityComponentManager::EntityComponentManager()
{
    // Initialize the list of free entity ids
    for (int i = 0; i < EntityComponentManager::MAXNUMBEROFENTITIES; i++){
        _availableEntityIds.push_back(i);
    }

    _componentTypesAdded = 0;
}

EntityComponentManager::~EntityComponentManager()
{
    // mark all entities as inactive, so that they are marked for cleanup
    while(_takenEntityIds.empty() == false){
        int entityId = _takenEntityIds.front();

        _takenEntityIds.pop_front();

        MarkEntityInactive(entityId);
    }

    DeleteAllInactiveEntities();

    // delete other misc memory shit

    //dtor

}

void EntityComponentManager::DeleteAllInactiveEntities(){
    // todo: remove inactive entities and clean up components
}

/// Get a count of active entities
int EntityComponentManager::GetEntitiesCount(){
    return _takenEntityIds.size();
}

/// Mark the given entity as inactive.
void EntityComponentManager::MarkEntityInactive(int entityId){
    _inactiveEntityIds.push_back(entityId);
}

/// Return the id of the added entity; if -1, an entity was not created. 0 is a valid id.
int EntityComponentManager::AddEntity(){
    int entityId = -1;

    if (_availableEntityIds.empty() == false){
        entityId = _availableEntityIds.front();

        _availableEntityIds.pop_front();
        _takenEntityIds.push_back(entityId);
    }

    return entityId;
}