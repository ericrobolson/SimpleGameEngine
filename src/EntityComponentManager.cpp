#include <list>
#include "EntityComponentManager.h"
#include <mutex>
using namespace ECS;

EntityComponentManager::EntityComponentManager()
{
        // Initialize the list of free entity ids
        for (int i = 0; i < MAXNUMBEROFENTITIES; i++){
            _availableEntityIds.push_back(i);
        }

        _componentTypesAdded = 0;
}

EntityComponentManager::~EntityComponentManager()
{
    // mark all entities as inactive, so that they are marked for cleanup

        while(_takenEntityIds.empty() == false){
            int entityId = _takenEntityIds.back();

            _takenEntityIds.pop_back();

            MarkEntityInactive(entityId);
        }

    DeleteAllInactiveEntities();

    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // todo: delete other misc memory shit

}

/// Return the id of the added entity
std::shared_ptr<int> EntityComponentManager::AddEntity(){
    int entityId = -1;

        if (_availableEntityIds.empty() == false){
            entityId = _availableEntityIds.back();

            _availableEntityIds.pop_back();
            _takenEntityIds.push_back(entityId);
        }

        if (entityId == -1){
            return nullptr;
        }

    return std::make_shared<int>(entityId);
}


/// Mark the given entity as inactive.
void EntityComponentManager::MarkEntityInactive(int entityId){
        _inactiveEntityIds.push_back(entityId);
}


void EntityComponentManager::DeleteAllInactiveEntities(){
    int entityId = -1;

        while (_inactiveEntityIds.empty() == false){
            entityId = _inactiveEntityIds.back();

            // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
            // todo: remove inactive entities and clean up components

            _inactiveEntityIds.pop_back();
            _availableEntityIds.push_back(entityId);
        }

        _takenEntityIds.clear();
}
