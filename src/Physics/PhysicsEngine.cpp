#include "PhysicsEngine.h"
#include "Aabb.h"

#include "PhysicsBodyComponent.h"

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

    // Get a list of all entities with Velocity != 0
    std::vector<int> movingEntityIds = ecs.Search<PhysicsBodyComponent>(
        [](PhysicsBodyComponent c){
            return (c.Body.Velocity.X != 0.0_fp && c.Body.Velocity.Y != 0.0_fp);
        });

    // TODO: Build quad tree?
    // TODO: Apply forces to vectors?
    // TODO: Calculate collisions
    // TODO: Resolve collisions
    // TODO: Update Positions
}
