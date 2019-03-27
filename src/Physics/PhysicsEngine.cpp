#include "PhysicsEngine.h"
#include "Aabb.h"

#include "PhysicsBodyComponent.h"
#include "CollisionDectector.h"
#include "CollisionData.h"
#include <memory>
#include <map>
#include <utility>
#include "Debugger.h"
#include <algorithm>

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
    j /= (cd.Entity1->Mass.InverseMass() + cd.Entity2->Mass.InverseMass());

    // Apply impulse and scale it by the mass of the two objects
    EVector impulse = cd.Normal * j;

    if (cd.Entity1->IsStaticObject && !cd.Entity2->IsStaticObject){
        cd.Entity2->Velocity += impulse;
    }else if (!cd.Entity1->IsStaticObject && cd.Entity2->IsStaticObject){
        cd.Entity1->Velocity -= impulse;
    }else{
        cd.Entity1->Velocity -= impulse * cd.Entity1->Mass.InverseMass();
        cd.Entity2->Velocity += impulse * cd.Entity2->Mass.InverseMass();
    }

    // Positional correction using linear projection; scale by total mass in system compared to the mass of the two entities
    const FixedPointInt positionalPercentCorrection = 0.1_fp; // .2 to .8
    const FixedPointInt slop = 0.2_fp; // .01 to .1
    FixedPointInt slopCorrection = (cd.Penetration - slop);
    FixedPointInt zero = 0.0_fp;
    slopCorrection = FixedPointInt::maximum(slopCorrection, zero);
    FixedPointInt totalMass = cd.Entity1->Mass.Mass + cd.Entity2->Mass.Mass;


    EVector correction = cd.Normal * positionalPercentCorrection * slopCorrection * (totalMass / (cd.Entity1->Mass.InverseMass() + cd.Entity2->Mass.InverseMass()));

    if (cd.Entity1->IsStaticObject == false){
        cd.Entity1->Transform.Position -= correction * cd.Entity1->Mass.InverseMass();
    }

    if (cd.Entity2->IsStaticObject == false){
        cd.Entity2->Transform.Position += correction * cd.Entity2->Mass.InverseMass();
    }
}



void PhysicsEngine::UpdatePhysics(FixedPointInt timeStep, ECS::EntityComponentManager &ecs, BucketTree& bucketTree){
    // Think of this as building a snapshot of a valid world
    // E.g. you pass in valid data, then when this is done running it leaves it in a valid state.


    // Get all entities from ECS which have a physics body
    std::vector<int> matchingEntityIds = ecs.Search<PhysicsBodyComponent>();

    // Reset the total mass in the system
    _totalMassInSystem.Value = 0;

    // Build buckettree
    bucketTree.FlushBuckets();

    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        int entityId = *it;

        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);



        bucketTree.AddEntity(component->Body.GetRoughAabb().MinCoordinate(), component->Body.GetRoughAabb().MaxCoordinate(), entityId);

        // Get total mass of the system; todo: good canidate for refactoring as it's not likely mass will change much so may only do it when adding/deleting entities?
        _totalMassInSystem += component->Body.Mass.Mass;
    }

    // Change to use projected entity positions, then resolve those. Make it so that entities never actually touch.
    // Whenever an entity is adjusted due to collision issues, recheck all collisions?




    // Get a list of all entities with Velocity != 0, as only those need to check for collisions that need to be resolved
    std::vector<int> movingEntityIds = ecs.SearchOn<PhysicsBodyComponent>(matchingEntityIds,
        [](PhysicsBodyComponent c){
            return (c.Body.Velocity.X != 0.0_fp || c.Body.Velocity.Y != 0.0_fp);
        });

    // Create a map of entities that have been checked
    std::map<std::pair<int, int>, bool> checkedEntities;

    CollisionDectector collisionDectector;


    std::vector<CollisionData> collisionManifolds;
    std::vector<int> entitiesWithoutCollisions = matchingEntityIds;


    // apply velocities
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(*it);
        if (component != nullptr){

            if (component->Body.IsStaticObject == false){
                component->Body.Transform.Position += component->Body.Velocity;
            }
        }
        //todo: recalculate what bucket it's' in?

    }


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
        EVector originalPosition = component->Body.Transform.Position;

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
            CollisionData collisionData;;
            collisionData.Entity1 = &component->Body; // is this not referencing the proper data?
            collisionData.Entity2 = &component2->Body; // is this not referencing the proper data?

            // Get the initial velocities, so that we can adjust if there's issues
            EVector entity1Velocity = component->Body.Velocity;
            EVector entity2Velocity = component2->Body.Velocity;

            if (collisionDectector.CheckCollision(collisionData)){
                    ResolveCollision(collisionData);

                    while (collisionDectector.CheckCollision(collisionData)){
                        FixedPointInt positionShift = 0.1_fp;

                        if (component->Body.IsStaticObject == false){
                            component->Body.Transform.Position -= entity1Velocity * 2.0_fp;
                        }

                        if (component2->Body.IsStaticObject == false){
                            component2->Body.Transform.Position -= entity2Velocity * 2.0_fp;
                        }

                        if (component2->Body.IsStaticObject && component->Body.IsStaticObject){
                            break;
                        }
                    }
                    // this part is key, but need to figure it out. Basically, when you create the collision, just separate bodies until there's no more collision

                    // goal; change from reactive to predictive collision detection?
            }
       }
    }

    // recalculate bucketTree based on new positions
    bucketTree.FlushBuckets();
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        int entityId = *it;

        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);



        bucketTree.AddEntity(component->Body.GetRoughAabb().MinCoordinate(), component->Body.GetRoughAabb().MaxCoordinate(), entityId);

        // Get total mass of the system; todo: good canidate for refactoring as it's not likely mass will change much so may only do it when adding/deleting entities?
    }


}
