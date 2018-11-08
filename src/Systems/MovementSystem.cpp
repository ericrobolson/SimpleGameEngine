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

#include "PlayerComponent.h"
#include "CanJumpComponent.h"
#include "HasJumpActionComponent.h"

const int MAXGRAVITYSPEED = 4;

MovementSystem::MovementSystem() : BaseSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}

bool MovementSystem::Process(ECS::EntityComponentManager &ecs){

    std::vector<int> entities = ecs.Search<MovementComponent>();

    std::vector<int>::iterator ptr;
    for (ptr = entities.begin(); ptr < entities.end(); ptr++){
        int entityId = *ptr;

        ThreadPool::Instance().submit([&ecs, entityId](){
            MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(entityId);

            // Apply gravity
            if (movementComponent.VerticalSpeed < MAXGRAVITYSPEED){
                movementComponent.VerticalSpeed +=.1;
            }

            // Player actions
            if (ecs.GetComponent<PlayerComponent>(entityId) != nullptr){
                // jump
                if (InputState::Instance().Button1IsPressed){
                    if (ecs.GetComponent<HasJumpActionComponent>(entityId) != nullptr){
                        if (ecs.GetComponent<CanJumpComponent>(entityId) != nullptr){
                            ecs.RemoveComponent<CanJumpComponent>(entityId);
                            movementComponent.VerticalSpeed =-4;
                        }
                    }
                }
            }
        });
    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}

