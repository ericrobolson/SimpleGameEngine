#include "ActionSystem.h"
#include "InputState.h"
#include <memory>
#include <vector>
#include "PhysicsBodyComponent.h"
#include <memory>
#include "RandomNumberGenerator.h"
#include "ActorComponent.h"
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

    FixedPointInt baseMoveSpeed = 0.02_fp * 2.0_fp; // should be even, as it's divided by 2
    FixedPointInt baseMaxMoveSpeed = baseMoveSpeed * 40.0_fp;
    FixedPointInt baseMoveReduction = 4.0_fp;


    // get entities
    std::vector<int> matchingEntityIds = ecs.Search<ActorComponent>();


    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> physicsComponent = ecs.GetComponent<PhysicsBodyComponent>(*it);
        std::shared_ptr<ActorComponent> actorComponent = ecs.GetComponent<ActorComponent>(*it);

        if (physicsComponent == nullptr || actorComponent == nullptr){
            continue;
        }

        FixedPointInt moveSpeed = baseMoveSpeed;
        FixedPointInt maxMoveSpeed = baseMaxMoveSpeed;

        if (actorComponent->PrimaryButtons.AButton == ActorComponent::ButtonState::Pressed){
            maxMoveSpeed = baseMaxMoveSpeed / baseMoveReduction;
        }

        if (actorComponent->LeftStick.LeftButton == ActorComponent::ButtonState::Pressed){
            ApplyMoveSpeed(physicsComponent->Body.Velocity.X, maxMoveSpeed, -moveSpeed);
        }

        if (actorComponent->LeftStick.RightButton == ActorComponent::ButtonState::Pressed){
            ApplyMoveSpeed(physicsComponent->Body.Velocity.X, maxMoveSpeed, moveSpeed);
        }

        if (actorComponent->LeftStick.UpButton == ActorComponent::ButtonState::Pressed){
            ApplyMoveSpeed(physicsComponent->Body.Velocity.Y, maxMoveSpeed, -moveSpeed);
        }

        if (actorComponent->LeftStick.DownButton == ActorComponent::ButtonState::Pressed){
            ApplyMoveSpeed(physicsComponent->Body.Velocity.Y, maxMoveSpeed, moveSpeed);
        }
    }

    return true;
}
