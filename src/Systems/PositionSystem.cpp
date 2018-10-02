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
    entities = ecs.Search<MovementComponent>(entities);

    for (std::size_t i = 0; i < entities.size(); i++){
        MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(i);
        PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(i);

        if (movementComponent.ForwardSpeed != 0 || movementComponent.HorizontalSpeed != 0){
            // Convert the angle of movement to X and Y
            positionComponent.PositionX = positionComponent.PositionX + movementComponent.GetXDelta();
            positionComponent.PositionY = positionComponent.PositionY + movementComponent.GetYDelta();
        }
    }

    return true;
}
