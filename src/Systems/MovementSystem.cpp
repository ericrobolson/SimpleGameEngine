#include <list>
#include <math.h>
#include "MovementSystem.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "InputState.h"
#include "Debugger.h"
#include <memory.h>

MovementSystem::MovementSystem() : BaseSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}


void HandlePlayerInput(MovementComponent &movementComponent, PositionComponent &positionComponent){
    const int moveSpeed = 5;


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
    std::vector<int> entities = ecs.Search<MovementComponent>();

    while (entities.empty() == false){
        int i = entities.back();
        entities.pop_back();

        MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(i);

        if (ecs.GetComponent<PlayerComponent>(i) != nullptr){
            std::shared_ptr<PositionComponent> positionPtr = ecs.GetComponent<PositionComponent>(i);

            if (positionPtr == nullptr){
                continue;
            }

            PositionComponent& positionComponent = *positionPtr.get();

            HandlePlayerInput(movementComponent, positionComponent);
        }

        if (ecs.GetComponent<EnemyComponent>(i) != nullptr){
           movementComponent.ForwardSpeed = 3;
           movementComponent.TurnLeft(2);
        }
    }


    return true;
}

