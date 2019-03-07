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

void PhysicsEngine::UpdatePhysics(FixedPointInt timeStep, ECS::EntityComponentManager &ecs){
    // Get all entities from ECS which have a physics body
    std::vector<int> matchingEntityIds = ecs.Search<PhysicsBodyComponent>();

    // Apply gravity?

    // Get a list of all entities with Velocity != 0
    std::vector<int> movingEntityIds = ecs.Search<PhysicsBodyComponent>(
        [](PhysicsBodyComponent c){
            return (c.Body.Velocity.X != 0.0_fp && c.Body.Velocity.Y != 0.0_fp);
        });

    // Build hashmap
    SpatialHashMap hashMap;
    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        hashMap.AddBody(*it, component->Body);
    }

    // TODO: Calculate collisions
    for (it = movingEntityIds.begin(); it != movingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        std::vector<int> entitiesToCheck = hashMap.GetEntityIds(component->Body.GetRoughAabb());

        // todo: do close collision checks
    }
    // TODO: Resolve collisions
    // TODO: Update Positions
}
