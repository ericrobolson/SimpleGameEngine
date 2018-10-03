#include <cstddef>

#include "PositionSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include "JobQueue.h"
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
    std::shared_ptr<MovementComponent> movementPtr = ecs.GetComponent<MovementComponent>(entityIndex);

    if (movementPtr == nullptr){
        return;
    }

    MovementComponent& movementComponent = *movementPtr;
    PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(entityIndex);

    if (movementComponent.ForwardSpeed != 0 || movementComponent.HorizontalSpeed != 0){
        // Convert the angle of movement to X and Y
        positionComponent.PositionX = positionComponent.PositionX + movementComponent.GetXDelta();
        positionComponent.PositionY = positionComponent.PositionY + movementComponent.GetYDelta();
    }
}

bool PositionSystem::Process(ECS::EntityComponentManager &ecs){

    return true;
    // ignore everything else for not

    std::list<int> entities = ecs.Search<PositionComponent>();


    int batchId = JobQueue::Instance().GetNextBatchId();

    for (std::size_t i = 0; i < entities.size(); i++){
        // make enqueue
        JobQueue::Instance().enqueue(batchId,[&ecs, i](){
            ProcessJob(ecs, i);
        });
    }

    while(JobQueue::Instance().DoJobsRemain(batchId)){
        // wait for jobs to finish
    }

    return true;
}


