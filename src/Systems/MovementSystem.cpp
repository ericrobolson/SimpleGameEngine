#include <list>
#include <memory>
#include "InputState.h"
#include "MovementSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "PlayerComponent.h"

MovementSystem::MovementSystem() : BaseSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}

bool MovementSystem::Process(ECS::EntityComponentManager &ecs){

    std::list<int> playerEntities = ecs.Search<PositionComponent>();

    for (int i = 0; i < playerEntities.size(); i++){
        std::shared_ptr<PlayerComponent> playerComponent = ecs.GetComponent<PlayerComponent>(i);
        PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(i);

        if (playerComponent != nullptr){
            int moveSpeed = 4;


            if (InputState::Instance().ButtonUpIsPressed){
                positionComponent.PositionY -= moveSpeed;
            }

            if (InputState::Instance().ButtonDownIsPressed){
                positionComponent.PositionY += moveSpeed;
            }

            if (InputState::Instance().ButtonLeftIsPressed){
                positionComponent.PositionX -= moveSpeed;
            }

             if (InputState::Instance().ButtonRightIsPressed){
                positionComponent.PositionX += moveSpeed;
            }
        }


    }




    return true;
}
