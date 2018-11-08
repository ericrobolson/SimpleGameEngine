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

enum CollisionType {NoCollision, HorizontalCollision, VerticalCollision};;

/// Check to see if two entities collided
CollisionType GetCollisionType(HitboxComponent entity1Hitbox, PositionComponent entity1Position, HitboxComponent entity2Hitbox, PositionComponent entity2Position){
    bool horizontalCollision = (entity1Position.PositionX < entity2Position.PositionX + entity2Hitbox.Width && entity1Position.PositionX + entity1Hitbox.Width > entity2Position.PositionX);
    bool verticalCollision = (entity1Position.PositionY < entity2Position.PositionY + entity2Hitbox.Height && entity1Position.PositionY + entity1Hitbox.Height > entity2Position.PositionY);

    if (!horizontalCollision && !verticalCollision){
        return CollisionType::NoCollision;
    } else if (horizontalCollision){
        return CollisionType::HorizontalCollision;
    } else{
        return CollisionType::VerticalCollision;
    }
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
        PositionComponent entity1Position = *ecs.GetComponent<PositionComponent>(entity1);

        HitboxComponent entity2Hitbox = *ecs.GetComponent<HitboxComponent>(entity2);
        PositionComponent entity2Position = *ecs.GetComponent<PositionComponent>(entity2);

        CollisionType collisionType = GetCollisionType(entity1Hitbox, entity1Position, entity2Hitbox, entity2Position);

        if (collisionType != CollisionType::NoCollision){

            if (ecs.GetComponent<ImpassibleComponent>(entity2) != nullptr){
                MovementComponent& movement = *ecs.GetComponent<MovementComponent>(entity1);

                if (collisionType == CollisionType::HorizontalCollision){
              //      position.PositionX -= movement.HorizontalSpeed;

                    bool movingRight = movement.HorizontalSpeed >= 0;
                    if (movingRight){
                        // move the position to the left so it's not overlapping
                        int moveToTheLeft = (entity1Position.PositionX + entity1Hitbox.Width) - entity2Position.PositionX;
                        entity1Position.PositionX -= moveToTheLeft;

                    }else{
                        // move the position to the right so it's not overlapping
                        int moveToTheRight = (entity2Position.PositionX + entity2Hitbox.Width) - entity1Position.PositionX;
                        entity1Position.PositionX += moveToTheRight;
                    }

                    movement.HorizontalSpeed = 0;
                }else{
                    // Vertical collision
                    bool movingDown = movement.VerticalSpeed >= 0;
                    if (movingDown){
                        // move the position to the left so it's not overlapping
                        int moveUp = (entity1Position.PositionY + entity1Hitbox.Height) - entity2Position.PositionY;
                        entity1Position.PositionY -= moveUp;

                    }else{
                        // move the position to the right so it's not overlapping
                        int moveDown = (entity2Position.PositionY + entity2Hitbox.Height) - entity1Position.PositionY;
                        entity1Position.PositionY += moveDown;
                    }
                   // position.PositionY -= movement.VerticalSpeed;
                    movement.VerticalSpeed = 0;
                }



            }
        }
    }
}

bool CollisionSystem::Process(ECS::EntityComponentManager &ecs){

    std::vector<int> entities = ecs.Search<HitboxComponent>();
    entities = ecs.SearchOn<PositionComponent>(entities);

    // Only need to process the moving entities
    std::vector<int> movingEntities = ecs.SearchOn<MovementComponent>(entities);


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
