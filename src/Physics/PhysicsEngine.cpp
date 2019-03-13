#include "PhysicsEngine.h"
#include "Aabb.h"

#include "PhysicsBodyComponent.h"
#include "SpatialHashMap.h"
#include "CollisionDectector.h"
#include "CollisionData.h"
#include <memory>
#include <map>
#include <utility>

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

void PhysicsEngine::ResolveCollision(CollisionData& cd){

    EVector relativeVelocity = cd.Entity2->Velocity - cd.Entity1->Velocity;

    // Calculate relative velocity in terms of the normal
    FixedPointInt velocityAlongNormal = rv.dot(cd.Normal);

    // Do not resolve if velocities are separating
    if (velocityAlongNormal > 0){
        return;
    }

    // Calculate restitution
    FixedPointInt e = FixedPointInt::min(cd.Entity1->Material.Restitution, cd.Entity2->Material.Restitution);

    // Calculate impulse scalar
float j = -(1 + e) * velAlongNormal
  j /= 1 / A.mass + 1 / B.mass
    // Apply impulse
Vec2 impulse = j * normal
  A.velocity -= 1 / A.mass * impulse
  B.velocity += 1 / B.mass * impulse

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

    // Create a map of entities that have been checked
    std::map<std::pair<int, int>, bool> checkedEntities;

    CollisionDectector collisionDectector;

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

            std::shared_ptr<PhysicsBodyComponent> component2 = ecs.GetComponent<PhysicsBodyComponent>(*it2);

            // Break out if neither has a component
            if (component == nullptr || component2 == nullptr){
                continue;
            }

            // Order the ids, as otherwise we'd end up doing duplicate checks. (entity1 and entity2) and (entity2 and entity1)
            OrderPair(entity1, entity2);

            std::pair<int, int> key(entity1, entity2);

            // if checked, continue to next entity
            auto checkedEntitiesResult = checkedEntities.find(key);
            if (checkedEntitiesResult != checkedEntities.end()){
                continue;
            }

            // if not, add to hashmap of checked entities,
            checkedEntities.insert(std::make_pair(key, true));

            // Check if there was a collision
            std::shared_ptr<CollisionData> collisionDataPtr = std::make_shared<CollisionData>();
            collisionDataPtr->Entity1 = std::make_shared<Body>(component->Body);
            collisionDataPtr->Entity2 = std::make_shared<Body>(component2->Body);

            if (collisionDectector.CheckCollision(collisionDataPtr)){
                // there was a collision, so resolve
            }
       }
    }
}
