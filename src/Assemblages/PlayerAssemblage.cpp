#include "PlayerAssemblage.h"
#include <memory>
#include "Entity.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "StaticSpriteComponent.h"
#include "PlayerComponent.h"

namespace PlayerAssemblage{
    std::shared_ptr<Entity> CreatePlayerEntity(){
        std::shared_ptr<Entity> playerEntity;


        std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>();
        std::shared_ptr<MovementComponent> movementComponent = std::make_shared<MovementComponent>();
        std::shared_ptr<StaticSpriteComponent> spriteComponent = std::make_shared<StaticSpriteComponent>();
        std::shared_ptr<PlayerComponent> playerComponent = std::make_shared<PlayerComponent>();

        playerEntity->AddComponent(positionComponent);
        playerEntity->AddComponent(movementComponent);
        playerEntity->AddComponent(spriteComponent);
        playerEntity->AddComponent(playerComponent);

        return playerEntity;
    }
}
