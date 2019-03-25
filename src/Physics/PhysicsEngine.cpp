#include "PhysicsEngine.h"
#include "Aabb.h"

#include "PhysicsBodyComponent.h"
#include "CollisionDectector.h"
#include "CollisionData.h"
#include <memory>
#include <map>
#include <utility>
#include "Debugger.h"

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
    FixedPointInt velocityAlongNormal = relativeVelocity.dot(cd.Normal);

    // Do not resolve if velocities are separating
    if (velocityAlongNormal.Value > 0){
        return;
    }

    // Calculate restitution
    FixedPointInt e = FixedPointInt::minimum(cd.Entity1->Material.Restitution, cd.Entity2->Material.Restitution);

    // Calculate impulse scalar
    FixedPointInt j = -(1.0_fp + e) * velocityAlongNormal;
    j /= cd.Entity1->Mass.InverseMass() + cd.Entity2->Mass.InverseMass();

    // Apply impulse and scale it by the mass of the two objects
    EVector impulse = cd.Normal * j;

    FixedPointInt massSum = cd.Entity1->Mass.Mass + cd.Entity2->Mass.Mass;

    FixedPointInt velocityRatio = cd.Entity1->Mass.Mass / massSum;
    cd.Entity1->Velocity -= impulse * velocityRatio;


    velocityRatio = cd.Entity2->Mass.Mass / massSum;
    cd.Entity2->Velocity += impulse * velocityRatio;

    // Positional correction using linear projection; scale by total mass in system compared to the mass of the two entities
    const FixedPointInt positionalPercentCorrection = 0.2_fp;
    EVector correction = cd.Normal * positionalPercentCorrection * (_totalMassInSystem / (cd.Entity1->Mass.InverseMass() + cd.Entity2->Mass.InverseMass()));
    cd.Entity1->Transform.Position -= correction * cd.Entity1->Mass.InverseMass();
    cd.Entity2->Transform.Position += correction * cd.Entity2->Mass.InverseMass();

    EVector evZero;
    cd.Entity1->Velocity = evZero;
    cd.Entity2->Velocity = evZero;
}



void PhysicsEngine::UpdatePhysics(FixedPointInt timeStep, ECS::EntityComponentManager &ecs, BucketTree& bucketTree){
    // Get all entities from ECS which have a physics body
    std::vector<int> matchingEntityIds = ecs.Search<PhysicsBodyComponent>();

    // Reset the total mass in the system
    _totalMassInSystem.Value = 0;

    // Build buckettree
    bucketTree.FlushBuckets();

    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        bucketTree.AddBody(*it, component->Body);

        // apply gravity
        EVector gravity;
        gravity.Y += 0.2_fp * component->Body.GravityScale;

        component->Body.Velocity += gravity;


        // Get total mass of the system; todo: good canidate for refactoring as it's not likely mass will change much so may only do it when adding/deleting entities?
        _totalMassInSystem += component->Body.Mass.Mass;
    }

    // Get a list of all entities with Velocity != 0, as only those need to check for collisions that need to be resolved
    std::vector<int> movingEntityIds = ecs.SearchOn<PhysicsBodyComponent>(matchingEntityIds,
        [](PhysicsBodyComponent c){
            return (c.Body.Velocity.X != 0.0_fp || c.Body.Velocity.Y != 0.0_fp);
        });

    // Create a map of entities that have been checked
    std::map<std::pair<int, int>, bool> checkedEntities;

    CollisionDectector collisionDectector;

    // Calculate collisions
    for (it = movingEntityIds.begin(); it != movingEntityIds.end(); it++){
        int entityId = *it;
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);

        if (component == nullptr){
            continue;
        }
        // Broad phase collision checks
        std::vector<int> entitiesToCheck = bucketTree.GetEntityIds(component->Body.GetRoughAabb());

        // Near phase collision checks and resolutions
        std::vector<int>::iterator it2;
        for (it2 = entitiesToCheck.begin(); it2 != entitiesToCheck.end(); it2++){
            SGE::Debugger::Instance().WriteMessage("Checking Possible collision...");

            int entity1 = entityId;
            int entity2 = *it2;

            if (entity1 == entity2){
                continue;
            }

            std::shared_ptr<PhysicsBodyComponent> component2 = ecs.GetComponent<PhysicsBodyComponent>(*it2);

            // Break out if neither has a component
            if (component2 == nullptr){
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
            collisionDataPtr->Entity1 = std::make_shared<Body>(component->Body); // is this not referencing the proper data?
            collisionDataPtr->Entity2 = std::make_shared<Body>(component2->Body); // is this not referencing the proper data?

            if (collisionDectector.CheckCollision(collisionDataPtr)){
                // there was a collision, so resolve
                ResolveCollision(*collisionDataPtr);

            }
       }
    }

    // apply velocities
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        //todo: recalculate what bucket it's' in?
        component->Body.Transform.Position += component->Body.Velocity;
    }

    // recalculate bucketTree based on new positions
    bucketTree.FlushBuckets();
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);

        bucketTree.AddBody(*it, component->Body);

    }
}
