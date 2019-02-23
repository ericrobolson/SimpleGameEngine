#include "PlayerAssemblage.h"
#include <memory>

#include "EntityComponentManager.h"

#include "PlayerComponent.h"

PlayerAssemblage::PlayerAssemblage()
{
    //ctor
}

PlayerAssemblage::~PlayerAssemblage()
{
    //dtor
}


std::shared_ptr<int> PlayerAssemblage::BuildPlayer(ECS::EntityComponentManager &ecs, int x, int y){
    std::shared_ptr<int> entityId = ecs.AddEntity();

    if (entityId != nullptr){
        int id = *entityId.get();

        PlayerComponent& playerComponent = ecs.AddComponent<PlayerComponent>(id);
    }

    return entityId;
}
