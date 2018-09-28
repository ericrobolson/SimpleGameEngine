#include "NewEntityComponentManager.h"
#include <memory>
#include <list>

using namespace ECS;

NewEntityComponentManager::NewEntityComponentManager()
{
    //ctor
}

NewEntityComponentManager::~NewEntityComponentManager()
{
    //dtor
}



/// Return the id of the added entity
std::shared_ptr<int> NewEntityComponentManager::AddEntity(){
    int entityId = -1;

    if (_availableEntityIds.empty() == false){
        entityId = _availableEntityIds.front();

        _availableEntityIds.pop_front();
        _takenEntityIds.push_back(entityId);
    }

    if (entityId == -1){
        return nullptr;
    }

    return std::make_shared<int>(entityId);
}


/// Mark the given entity as inactive.
void NewEntityComponentManager::MarkEntityInactive(int entityId){
    _inactiveEntityIds.push_back(entityId);
}


void NewEntityComponentManager::DeleteAllInactiveEntities(){
    int entityId = -1;

    while (_inactiveEntityIds.empty() == false){
        entityId = _inactiveEntityIds.front();

        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        // todo: remove inactive entities and clean up components

        _inactiveEntityIds.pop_front();
        _availableEntityIds.push_back(entityId);
        _takenEntityIds.remove(entityId);
    }
}
