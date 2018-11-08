#include "PlayerAssemblage.h"
#include <memory>

#include "EntityComponentManager.h"

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"

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

        HitboxComponent& hitBox = ecs.AddComponent<HitboxComponent>(id);
        hitBox.Height = 8;
        hitBox.Width = 8;

        MovementComponent& movementComponent = ecs.AddComponent<MovementComponent>(id);
        PlayerComponent& playerComponent = ecs.AddComponent<PlayerComponent>(id);

        PositionComponent& positionComponent = ecs.AddComponent<PositionComponent>(id);
        positionComponent.PositionX = x;
        positionComponent.PositionY = y;
    }

    return entityId;
}
