#include "PhysicsEngine.h"
#include "Aabb.h"

#include "PhysicsBodyComponent.h"
#include "SpatialHashMap.h"
#include <memory>
using namespace SGE_Physics;

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
    //dtor
}

// Given two integers, order them in a consistent manner
void OrderPair(int& a, int& b){
    int i = a;

    if (a > b){
        a = b;
        b = i;
    }
}

void PhysicsEngine::UpdatePhysics(FixedPointInt timeStep, ECS::EntityComponentManager &ecs){
    // Get all entities from ECS which have a physics body
    std::vector<int> matchingEntityIds = ecs.Search<PhysicsBodyComponent>();

    // Apply gravity?

    // Build hashmap
    SpatialHashMap hashMap;
    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        hashMap.AddBody(*it, component->Body);
    }

    // Get a list of all entities with Velocity != 0, as only those need to check for collisions that need to be resolved
    std::vector<int> movingEntityIds = ecs.SearchOn<PhysicsBodyComponent>(matchingEntityIds,
        [](PhysicsBodyComponent c){
            return (c.Body.Velocity.X != 0.0_fp && c.Body.Velocity.Y != 0.0_fp);
        });

    // Calculate collisions
    for (it = movingEntityIds.begin(); it != movingEntityIds.end(); it++){
        int entityId = *it;
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);

        // Broad phase collision checks
        std::vector<int> entitiesToCheck = hashMap.GetEntityIds(component->Body.GetRoughAabb());

        // Near phase collision checks and resolutions
        std::vector<int>::iterator it2;
        for (it2 = entitiesToCheck.begin(); it2 != entitiesToCheck.end(); it2++){
            int entity1 = entityId;
            int entity2 = *it2;

            // Order the ids, as otherwise we'd end up doing duplicate checks. (entity1 and entity2) and (entity2 and entity1)
            OrderPair(entity1, entity2);

            // if checked, continue to next entity
            // if not, add to hashmap of checked entities,
            // resolve collision
       }



    }
}
