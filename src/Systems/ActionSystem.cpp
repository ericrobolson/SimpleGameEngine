#include "ActionSystem.h"
#include "InputState.h"
#include <memory>
#include <vector>
#include "PlayerComponent.h"
#include "PhysicsBodyComponent.h"
#include <memory>
#include "RandomNumberGenerator.h"
ActionSystem::ActionSystem() : BaseSystem()
{
    //ctor
}

ActionSystem::~ActionSystem()
{
    //dtor
}


void ApplyMoveSpeed(FixedPointInt& vectorAxis, FixedPointInt maxMoveSpeed, FixedPointInt moveSpeed){
    vectorAxis += moveSpeed;

    if (vectorAxis > maxMoveSpeed){
        vectorAxis = maxMoveSpeed;
    } else if (vectorAxis < -maxMoveSpeed){
        vectorAxis = -maxMoveSpeed;
    }
}

bool ActionSystem::Process(ECS::EntityComponentManager &ecs){

    // Get player entities

    // do boundary checks, e.g. if moving faster than X speed left, where X is the max normal move speed, don't do anything

    FixedPointInt baseMoveSpeed = 0.03_fp * 2.0_fp; // should be even, as it's divided by 2
    FixedPointInt baseMaxMoveSpeed = baseMoveSpeed * 40.0_fp;
    FixedPointInt baseMoveReduction = 4.0_fp;


    // get entities
    std::vector<int> matchingEntityIds = ecs.Search<PlayerComponent>();


    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        if (component == nullptr){
            continue;
        }

        FixedPointInt moveSpeed = baseMoveSpeed;
        FixedPointInt maxMoveSpeed = baseMaxMoveSpeed;

        if (InputState::Instance().Button1IsPressed){
            maxMoveSpeed = baseMaxMoveSpeed / baseMoveReduction;
        }

        if (InputState::Instance().ButtonLeftIsPressed){
            ApplyMoveSpeed(component->Body.Velocity.X, maxMoveSpeed, -moveSpeed);
        }

        if (InputState::Instance().ButtonRightIsPressed){
            ApplyMoveSpeed(component->Body.Velocity.X, maxMoveSpeed, moveSpeed);
        }

        if (InputState::Instance().ButtonUpIsPressed){
            ApplyMoveSpeed(component->Body.Velocity.Y, maxMoveSpeed, -moveSpeed);
        }

        if (InputState::Instance().ButtonDownIsPressed){
            ApplyMoveSpeed(component->Body.Velocity.Y, maxMoveSpeed, moveSpeed);
        }
    }

    return true;
}
