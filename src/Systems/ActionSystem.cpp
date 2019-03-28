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


bool ActionSystem::Process(ECS::EntityComponentManager &ecs){

    // Get player entities

    // do boundary checks, e.g. if moving faster than X speed left, where X is the max normal move speed, don't do anything

     FixedPointInt moveSpeed = 0.03_fp;
     FixedPointInt jumpSpeed = 50.0_fp;

    // get entities
    std::vector<int> matchingEntityIds = ecs.Search<PlayerComponent>();


    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        if (component == nullptr){
            continue;
        }

        if (InputState::Instance().ButtonLeftIsPressed){
            component->Body.Velocity.X -= moveSpeed;
        }

        if (InputState::Instance().ButtonRightIsPressed){
            component->Body.Velocity.X += moveSpeed;
        }

        if (InputState::Instance().ButtonUpIsPressed){
            component->Body.Force.Y = -jumpSpeed;
        }

        if (InputState::Instance().ButtonDownIsPressed){
            component->Body.Velocity.Y += moveSpeed;
        }
    }

    return true;
}
