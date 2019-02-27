#include "PhysicsEngine.h"
#include "Aabb.h"
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

    // Build quad tree?
    // Get a list of all entities with Velocity != 0
    // Apply forces to vectors?
    // Calculate collisions
    // Resolve collisions
    // Update Positions
}
