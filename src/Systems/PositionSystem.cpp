#include <cstddef>

#include "PositionSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include <mutex>
#include "ThreadPool.h"

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

    positionComponent.PositionX += movementComponent.HorizontalSpeed;
    positionComponent.PositionY += movementComponent.VerticalSpeed; // Since a positive vspeed means it's moving up, need to reverse it
}

bool PositionSystem::Process(ECS::EntityComponentManager &ecs){

    // ignore everything else for not
    std::vector<int> entities = ecs.Search<PositionComponent>();
    entities = ecs.SearchOn<MovementComponent>(entities);


    std::vector<int>::iterator it;

    for (it = entities.begin(); it != entities.end(); ++it){
        int entityId = *it;

        ThreadPool::Instance().submit([&ecs, entityId](){
                                          ProcessJob(ecs, entityId);
                                      });
    }

    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}


