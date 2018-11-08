#include "CollisionSystem.h"
#include "EntityComponentManager.h"
#include "GameState.h"
#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "PositionComponent.h"
#include "ThreadPool.h"
#include "ImpassibleComponent.h"
#include <future>



CollisionSystem::CollisionSystem()
{
    //ctor
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

/// Check to see if two entities collided
bool Collided(int entity1, int entity2, ECS::EntityComponentManager &ecs){
    HitboxComponent entity1Hitbox = *ecs.GetComponent<HitboxComponent>(entity1);
    PositionComponent entity1Position = *ecs.GetComponent<PositionComponent>(entity1);

    HitboxComponent entity2Hitbox = *ecs.GetComponent<HitboxComponent>(entity2);
    PositionComponent entity2Position = *ecs.GetComponent<PositionComponent>(entity2);

    return (entity1Position.PositionX < entity2Position.PositionX + entity2Hitbox.Width &&
       entity1Position.PositionX + entity1Hitbox.Width > entity2Position.PositionX &&
       entity1Position.PositionY < entity2Position.PositionY + entity2Hitbox.Height &&
       entity1Position.PositionY + entity1Hitbox.Height > entity2Position.PositionY);
}

void ProcessEntity(int movingEntity, ECS::EntityComponentManager &ecs, std::vector<int> entitiesToCheck){
    std::vector<int>::iterator ptr;
    for (ptr = entitiesToCheck.begin(); ptr < entitiesToCheck.end(); ptr++){
        int entity2 = *ptr;

        // Skip checking itself
        if (movingEntity == entity2){
            continue;
        }

        if (Collided(movingEntity, entity2, ecs)){
            if (ecs.GetComponent<ImpassibleComponent>(entity2) != nullptr){
                MovementComponent& movement = *ecs.GetComponent<MovementComponent>(movingEntity);
                movement.VerticalSpeed = 0;
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

        ThreadPool::Instance().submit([&ecs, entityId, entities](){
            ProcessEntity(entityId, ecs, entities);
                                      });
    }


    std::future<bool> isDone = ThreadPool::Instance().submit([](){ return true; });

    return isDone.get();
}
