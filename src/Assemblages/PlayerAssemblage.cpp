#include "PlayerAssemblage.h"
#include <memory>
#include "Entity.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "StaticSpriteComponent.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"

namespace PlayerAssemblage{
    std::shared_ptr<Entity> CreatePlayerEntity(){
        std::shared_ptr<Entity> playerEntity;


        PositionComponent positionComponent;
        MovementComponent movementComponent;
        StaticSpriteComponent spriteComponent;


        HealthComponent healthComponent;

        PlayerComponent playerComponent;

        playerEntity->AddComponent(positionComponent);
        playerEntity->AddComponent(healthComponent);
        playerEntity->AddComponent(movementComponent);
        playerEntity->AddComponent(spriteComponent);
        playerEntity->AddComponent(playerComponent);

        return playerEntity;
    }
}
