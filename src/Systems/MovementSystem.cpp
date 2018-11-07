#include <list>
#include <math.h>
#include "MovementSystem.h"
#include "EntityComponentManager.h"
#include<future>
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "InputState.h"
#include "Debugger.h"
#include <memory.h>
#include "ThreadPool.h"
#include <chrono>

MovementSystem::MovementSystem() : BaseSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void HandlePlayerInput(MovementComponent &movementComponent, PositionComponent &positionComponent){

}

bool MovementSystem::Process(ECS::EntityComponentManager &ecs){

    std::vector<int> entities = ecs.Search<MovementComponent>();

    std::vector<int>::iterator ptr;
    int index = 0;
    for (ptr = entities.begin(); ptr < entities.end(); ptr++){
        int entityId = *ptr;

        ThreadPool::Instance().submit([&ecs, entityId](){

        MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(entityId);

/*
        if (ecs.GetComponent<PlayerComponent>(entityId) != nullptr){
            std::shared_ptr<PositionComponent> positionPtr = ecs.GetComponent<PositionComponent>(entityId);

            if (positionPtr == nullptr){
                return;
            }

            PositionComponent& positionComponent = *positionPtr.get();

            HandlePlayerInput(movementComponent, positionComponent);
        }
        */

        });

        index++;

    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}

