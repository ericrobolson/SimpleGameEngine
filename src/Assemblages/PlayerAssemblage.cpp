#include "PlayerAssemblage.h"
#include <memory>

#include "EntityComponentManager.h"

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "ImpassibleComponent.h"
#include "HasJumpActionComponent.h"
#include "DeckComponent.h"
#include "VisibleComponent.h"


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
        hitBox.SetHeight(8);
        hitBox.SetWidth(8);

        MovementComponent& movementComponent = ecs.AddComponent<MovementComponent>(id);
        PlayerComponent& playerComponent = ecs.AddComponent<PlayerComponent>(id);

        PositionComponent& positionComponent = ecs.AddComponent<PositionComponent>(id);
        positionComponent.PositionX = x;
        positionComponent.PositionY = y;

        ecs.AddComponent<ImpassibleComponent>(id);
        ecs.AddComponent<HasJumpActionComponent>(id);

        ecs.AddComponent<VisibleComponent>(id);

        DeckComponent& deck = ecs.AddComponent<DeckComponent>(id);
        deck.SetEnergy(3);

    }

    return entityId;
}
