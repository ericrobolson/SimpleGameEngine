#include <cstddef>

#include "PositionSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include <mutex>

PositionSystem::PositionSystem() : BaseSystem()
{
    //ctor
}

PositionSystem::~PositionSystem()
{
    //dtor
}

void ProcessJob(ECS::EntityComponentManager &ecs, int entityIndex){
    MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(entityIndex);
    PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(entityIndex);

    if (movementComponent.ForwardSpeed != 0 || movementComponent.HorizontalSpeed != 0){
        // Convert the angle of movement to X and Y
        positionComponent.PositionX = positionComponent.PositionX + movementComponent.GetXDelta();
        positionComponent.PositionY = positionComponent.PositionY + movementComponent.GetYDelta();
    }
}

bool PositionSystem::Process(ECS::EntityComponentManager &ecs){

    // ignore everything else for not

    ecs.Lock();
    std::vector<int> entities = ecs.Search<PositionComponent>();
    entities = ecs.SearchOn<MovementComponent>(entities);

    std::vector<int>::iterator it;

    for (it = entities.begin(); it != entities.end(); ++it){
        int entityId = *it;

        ProcessJob(ecs, entityId);
    }

    ecs.Unlock();
    return true;
}


