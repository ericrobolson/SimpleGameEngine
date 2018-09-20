#include "BaseSystem.h"
#include "Entity.h"

BaseSystem::BaseSystem()
{
    //ctor
}

BaseSystem::~BaseSystem()
{
    //dtor
}

bool BaseSystem::Process(std::vector<std::shared_ptr<Entity>>& entities){
    // this is where a system processes entities
    return true;
};
