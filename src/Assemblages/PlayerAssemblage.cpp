#include "PlayerAssemblage.h"
#include <memory>
#include "Entity.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "StaticSpriteComponent.h"

namespace PlayerAssemblage{
    std::shared_ptr<Entity> CreatePlayerEntity(){
        std::shared_ptr<Entity> playerEntity;


        std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>();
        std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>();
        std::shared_ptr<StaticSpriteComponent> spriteComponent = std::make_shared<StaticSpriteComponent>();



        playerEntity->AddComponent(positionComponent);
        playerEntity->AddComponent(movementComponent);
        playerEntity->AddComponent(spriteComponent);

        return playerEntity;

    }
}
