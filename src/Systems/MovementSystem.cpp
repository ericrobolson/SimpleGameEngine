#include <list>
#include <math.h>
#include "MovementSystem.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include<future>
#include "EnemyComponent.h"
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

bool MovementSystem::Process(ECS::EntityComponentManager &ecs){

    ecs.Lock();
        std::vector<int> entities = ecs.Search<MovementComponent>();
    ecs.Unlock();

    std::vector<int>::iterator ptr;
    int index = 0;
    for (ptr = entities.begin(); ptr < entities.end(); ptr++){
        int entityId = *ptr;

        ThreadPool::Instance().submit([&ecs, entityId](){

        ecs.Lock();
        MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(entityId);

        if (ecs.GetComponent<EnemyComponent>(entityId) != nullptr){
           movementComponent.ForwardSpeed = 2;
           movementComponent.TurnLeft(15);
        }

        ecs.Unlock();

        });

        index++;

    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}

