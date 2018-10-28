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
    const int moveSpeed = 2;


    InputState& inputState = InputState::Instance();

    // Calculate horizontal and vertical movement
    if (inputState.ButtonUpIsPressed){
        movementComponent.ForwardSpeed = moveSpeed;
    }

    if (inputState.ButtonDownIsPressed){
        movementComponent.ForwardSpeed = -moveSpeed;
    }

    if (inputState.ButtonRightIsPressed){
        movementComponent.HorizontalSpeed = moveSpeed;
    }

    if (inputState.ButtonLeftIsPressed){
        movementComponent.HorizontalSpeed = -moveSpeed;
    }

    if ((!inputState.ButtonUpIsPressed && !inputState.ButtonDownIsPressed)
        || (inputState.ButtonUpIsPressed && inputState.ButtonDownIsPressed)){
        movementComponent.ForwardSpeed = 0;
    }

     if ((!inputState.ButtonRightIsPressed && !inputState.ButtonLeftIsPressed)
        || (inputState.ButtonRightIsPressed && inputState.ButtonLeftIsPressed)){
        movementComponent.HorizontalSpeed = 0;
    }

    // Calculate the angle based of the cursor

    movementComponent.SetDirectionAngleFromCoordinates(positionComponent.PositionX, positionComponent.PositionY, inputState.CursorX, inputState.CursorY);
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
        ecs.Unlock();

        });

        index++;

    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}

