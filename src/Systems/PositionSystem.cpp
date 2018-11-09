#include <cstddef>

#include "PositionSystem.h"
#include "EntityComponentManager.h"
#include "PositionComponent.h"
#include "MovementComponent.h"
#include <mutex>
#include "ThreadPool.h"
#include "HitboxComponent.h"
#include "GameState.h"

PositionSystem::PositionSystem() : BaseSystem()
{
    //ctor
}

PositionSystem::~PositionSystem()
{
    //dtor
}

void ProcessJob(ECS::EntityComponentManager &ecs, int entityIndex){
    MovementComponent& movementComponent = *ecs.GetComponent<MovementComponent>(entityIndex);
    PositionComponent& positionComponent = *ecs.GetComponent<PositionComponent>(entityIndex);

    positionComponent.PositionX += movementComponent.HorizontalSpeed;
    positionComponent.PositionY += movementComponent.VerticalSpeed; // Since a positive vspeed means it's moving up, need to reverse it

    // Prevent it from going out of the game window
    int hitboxWidth = 0;
    int hitboxHeight = 0;

    std::shared_ptr<HitboxComponent> hitboxComponentPtr = ecs.GetComponent<HitboxComponent>(entityIndex);
    if (hitboxComponentPtr != nullptr){
        hitboxWidth = hitboxComponentPtr->GetWidth();
        hitboxHeight = hitboxComponentPtr->GetHeight();
    }

    if ((positionComponent.PositionX + hitboxWidth) > GameState::LevelWidth){
        positionComponent.PositionX = GameState::LevelWidth - hitboxWidth;
        movementComponent.HorizontalSpeed = 0;
    }

    if (positionComponent.PositionX < 0){
        positionComponent.PositionX = 0;
        movementComponent.HorizontalSpeed = 0;
    }

    if ((positionComponent.PositionY + hitboxWidth) > GameState::LevelHeight){
        positionComponent.PositionY = GameState::LevelHeight - hitboxHeight;
        movementComponent.VerticalSpeed = 0;
    }

    if (positionComponent.PositionY < 0){
        positionComponent.PositionY = 0;
        movementComponent.VerticalSpeed = 0;
    }
}

bool PositionSystem::Process(ECS::EntityComponentManager &ecs){

    // ignore everything else for not
    std::vector<int> entities = ecs.Search<PositionComponent>();
    entities = ecs.SearchOn<MovementComponent>(entities);


    std::vector<int>::iterator it;

    for (it = entities.begin(); it != entities.end(); ++it){
        int entityId = *it;

        ThreadPool::Instance().submit([&ecs, entityId](){
                                          ProcessJob(ecs, entityId);
                                      });
    }

    std::future<bool> isDone = ThreadPool::Instance().submit([](){

                                                        return true;
                                                        });
    return isDone.get();
}


