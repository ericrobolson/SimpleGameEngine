#include <cstddef>

#include "PositionSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
PositionSystem::PositionSystem() : BaseSystem()
{
    //ctor
}

PositionSystem::~PositionSystem()
{
    //dtor
}


bool PositionSystem::Process(ECS::EntityComponentManager &ecs){

    std::list<int> entities = ecs.Search<PositionComponent>();


    for (std::size_t i = 0; i < entities.size(); i++){
        std::shared_ptr<MovementComponent> movementPtr = ecs.GetComponent<MovementComponent>(i);
        if (movementPtr == nullptr){
            continue;
        }

        MovementComponent& movementComponent = *movementPtr;
        PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(i);

        if (movementComponent.ForwardSpeed != 0 || movementComponent.HorizontalSpeed != 0){
            // Convert the angle of movement to X and Y
            positionComponent.PositionX = positionComponent.PositionX + movementComponent.GetXDelta();
            positionComponent.PositionY = positionComponent.PositionY + movementComponent.GetYDelta();
        }
    }

    return true;
}
