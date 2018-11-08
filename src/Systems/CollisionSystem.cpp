#include "CollisionSystem.h"
#include "EntityComponentManager.h"
#include "GameState.h"
#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "PositionComponent.h"
#include "ThreadPool.h"
#include "ImpassibleComponent.h"
#include <future>
#include <memory>


CollisionSystem::CollisionSystem()
{
    //ctor
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

/// Check to see if two entities collided
bool IsCollision(HitboxComponent entity1Hitbox, int entity1PositionX, int entity1PositionY, HitboxComponent entity2Hitbox, PositionComponent entity2Position){
    bool inHorizontalBounds = (entity1PositionX < entity2Position.PositionX + entity2Hitbox.GetWidth() && entity1PositionX + entity1Hitbox.GetWidth() > entity2Position.PositionX);
    bool inVerticalBounds = (entity1PositionY < entity2Position.PositionY + entity2Hitbox.GetHeight() && entity1PositionY + entity1Hitbox.GetHeight() > entity2Position.PositionY);

    return (inHorizontalBounds && inVerticalBounds);
}

void ProcessEntity(int entity1, ECS::EntityComponentManager &ecs, std::vector<int> entitiesToCheck){
    std::vector<int>::iterator ptr;
    for (ptr = entitiesToCheck.begin(); ptr < entitiesToCheck.end(); ptr++){
        int entity2 = *ptr;

        // Skip checking itself
        if (entity1 == entity2){
            continue;
        }

        HitboxComponent entity1Hitbox = *ecs.GetComponent<HitboxComponent>(entity1);
        PositionComponent& entity1Position = *ecs.GetComponent<PositionComponent>(entity1);

        HitboxComponent entity2Hitbox = *ecs.GetComponent<HitboxComponent>(entity2);
        PositionComponent entity2Position = *ecs.GetComponent<PositionComponent>(entity2);
        MovementComponent& movement = *ecs.GetComponent<MovementComponent>(entity1);

        int entity1PositionX = entity1Position.PositionX + movement.HorizontalSpeed;
        int entity1PositionY = entity1Position.PositionY + movement.VerticalSpeed;

        if (IsCollision(entity1Hitbox, entity1PositionX, entity1PositionY, entity2Hitbox, entity2Position)){
            if (ecs.GetComponent<ImpassibleComponent>(entity2) != nullptr){

                /* Need to do horizontal collision checking


                bool inHorizontalBounds = (entity1Position.PositionX < entity2Position.PositionX + entity2Hitbox.GetWidth() && entity1Position.PositionX + entity1Hitbox.GetWidth() > entity2Position.PositionX);

                if (inHorizontalBounds){
                    // Prevent hitboxes from overlapping
                    bool shiftRight = entity1Position.PositionX < (entity2Position.PositionX + entity2Hitbox.GetWidth());
                    if (shiftRight){
                        entity1Position.PositionX = (entity2Position.PositionX + entity2Hitbox.GetWidth());
                    }else{
                        entity1Position.PositionX = (entity2Position.PositionX - entity1Hitbox.GetWidth());
                    }
                }
                */
                bool inVerticalBounds = (entity1PositionY < entity2Position.PositionY + entity2Hitbox.GetHeight() && entity1PositionY + entity1Hitbox.GetHeight() > entity2Position.PositionY);
                if (inVerticalBounds && movement.VerticalSpeed != 0){
                    movement.VerticalSpeed = 0;

                    // Prevent it from going further down
                    if (entity1Position.PositionY < entity2Position.PositionY){
                        entity1Position.PositionY = (entity2Position.PositionY - entity1Hitbox.GetHeight());
                    }
                    // prevent it from going further up
                    else {
                        entity1Position.PositionY = (entity2Position.PositionY + entity2Hitbox.GetHeight());
                    }
                }
            }
        }
    }
}

bool CollisionSystem::Process(ECS::EntityComponentManager &ecs){

    std::vector<int> entities = ecs.Search<HitboxComponent>();
    entities = ecs.SearchOn<PositionComponent>(entities);

    // Only need to process the moving entities
    std::vector<int> movingEntities = ecs.SearchOn<MovementComponent>(entities, [](MovementComponent c){
                                                                        if (c.HorizontalSpeed != 0 || c.VerticalSpeed != 0){
                                                                        return true;
                                                                      }

                                                                        return false;
                                                                      }); // todo: query to only get things with movespeed != 0


    std::vector<int>::iterator ptr;
    for (ptr = movingEntities.begin(); ptr < movingEntities.end(); ptr++){
        int entityId = *ptr;

        //TOdo: update to use a more optimal structure for collisions, as it stands it checks all of them
        ThreadPool::Instance().submit([&ecs, entityId, entities](){
            ProcessEntity(entityId, ecs, entities);
                                      });
    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){ return true; });

    return isDone.get();
}
