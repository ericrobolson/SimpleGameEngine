#include <list>
#include <math.h>
#include "MovementSystem.h"
#include "EntityComponentManager.h"
#include "PlayerComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "InputState.h"
#include "Debugger.h"


MovementSystem::MovementSystem() : BaseSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}

bool MovementSystem::Process(ECS::EntityComponentManager &ecs){

    std::list<int> entities = ecs.Search<PlayerComponent>();
    entities = ecs.Search<MovementComponent>(entities);
    entities = ecs.Search<PositionComponent>(entities);

    const int moveSpeed = 5;

    for (int i = 0; i < entities.size(); i++){
        MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(i);

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
        PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(i);

        movementComponent.SetDirectionAngleFromCoordinates(positionComponent.PositionX, positionComponent.PositionY, inputState.CursorX, inputState.CursorY);

    }

    return true;
}
