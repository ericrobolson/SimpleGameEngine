#include "PhysicsEngine.h"
#include "Aabb.h"
#include "PhysicsBodyComponent.h"
#include "CollisionDectector.h"
#include "CollisionData.h"
#include <memory>
#include <unordered_map>
#include <map>
#include <utility>
#include "Debugger.h"
#include <algorithm>

using namespace SGE_Physics;


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

void ApplyFriction(Body& body, FixedPointInt otherEntityFriction){

    FixedPointInt friction = (body.Material.Friction + otherEntityFriction) / 2.0_fp;

    EVector frictionVector = body.Velocity / body.Velocity; // scale it so we just get the direction

    // ensure that it's facing the right way; if pointing same direction need to flip so it applies opposite force
    if (frictionVector.dot(body.Velocity) >= 0.0_fp){
        frictionVector = -frictionVector;
    }

    body.Velocity += frictionVector * friction * body.Mass.InverseMass();
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

    cd.Entity1->Velocity -= impulse * cd.Entity1->Mass.InverseMass();
    cd.Entity2->Velocity += impulse * cd.Entity2->Mass.InverseMass();

    return;
}



void PhysicsEngine::UpdatePhysics(FixedPointInt hz, ECS::EntityComponentManager &ecs, BucketTree& bucketTree){
    // Think of this as building a snapshot of a valid world
    // E.g. you pass in valid data, then when this is done running it leaves it in a valid state.

    EVector gravityVector;
    gravityVector = (PhysicsEngine::GetGravity() / hz);

    // Get all entities from ECS which have a physics body
    std::vector<int> matchingEntityIds = ecs.Search<PhysicsBodyComponent>();

    // Build buckettree
    bucketTree.FlushBuckets();

    EVector evZero;

    std::vector<int> movingEntityIds;

    std::vector<int>::iterator it;
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        int entityId = *it;

        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);

        component->Body.Force += gravityVector * component->Body.Mass.Mass;
        component->Body.Velocity += (component->Body.Force * component->Body.Mass.InverseMass());

        // Reset force
        component->Body.Force = evZero;

        // Project collisions
        EVector minCoordinate = component->Body.GetRoughAabb().MinCoordinate();
        EVector maxCoordinate = component->Body.GetRoughAabb().MaxCoordinate();

        // Create bucket tree using projected positions
        minCoordinate += component->Body.Velocity;
        maxCoordinate += component->Body.Velocity;

        bucketTree.AddEntity(minCoordinate, maxCoordinate, entityId);

        // Add to list of objects to check for collisions
        if (component->Body.Velocity != evZero){
            movingEntityIds.push_back(entityId);
        }
    }

    // loop until all collisions are resolved, or X number of iterations have completed
    // NOTE: reduce counter for performance increases, but you'll lose out on collision resolution accuracy
    bool noCollisions;
    int counter = 20;

    // keep a list of entities to apply friction to
    std::unordered_map<int, FixedPointInt> entitiesThatGetFriction;

    do{
        noCollisions = true;

        // Create a map of entities that have been checked
        std::map<std::pair<int, int>, bool> checkedEntities;

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
                int entity1 = entityId;
                int entity2 = *it2;

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

                // if same entity, continue
                if (entity1 == entity2){
                    continue;
                }

                // Break out if neither has a component
                std::shared_ptr<PhysicsBodyComponent> component2 = ecs.GetComponent<PhysicsBodyComponent>(*it2);

                if (component2 == nullptr){
                    continue;
                }

                // Check if there was a collision
                CollisionData collisionData;;
                collisionData.Entity1 = &component->Body;
                collisionData.Entity2 = &component2->Body;

                // Get the original positions
                EVector entity1OriginalPosition = component->Body.Transform.Position;
                EVector entity2OriginalPosition = component2->Body.Transform.Position;

                // Apply the velocities to check if the objects will collide
                component->Body.Transform.Position += component->Body.Velocity;
                component2->Body.Transform.Position += component2->Body.Velocity;

                bool collided = CollisionDectector::CheckCollision(collisionData);

                // Reset original positions
                component->Body.Transform.Position = entity1OriginalPosition;
                component2->Body.Transform.Position = entity2OriginalPosition;

                if (collided){
                    ResolveCollision(collisionData);
                    noCollisions = false;

                    // Note: apply friction after calculating the collision vectors, as otherwise it would lead to incorrect calculations
                    // use iterators to get entity ids as the other ids have been ordered
                    entitiesThatGetFriction.insert({*it, component2->Body.Material.Friction});
                    entitiesThatGetFriction.insert({*it2, component->Body.Material.Friction});
                }
           }
        }

    counter--;
    }while(counter > 0 && noCollisions == false);

    // Apply friction
    std::unordered_map<int, FixedPointInt>::iterator frictionEntity;
    for (frictionEntity = entitiesThatGetFriction.begin(); frictionEntity != entitiesThatGetFriction.end(); frictionEntity++){
        int i = frictionEntity->first;
        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(i);

        if (component == nullptr){
            continue;
        }

        // Note: since friction is always a decreasing force, it will never result in a collision as collisions have been resolved
        ApplyFriction(component->Body, frictionEntity->second);
    }

    // Apply velocities and recalculate bucketTree
    bucketTree.FlushBuckets();
    for (it = matchingEntityIds.begin(); it != matchingEntityIds.end(); it++){
        int entityId = *it;

        std::shared_ptr<PhysicsBodyComponent> component = ecs.GetComponent<PhysicsBodyComponent>(entityId);

        component->Body.Transform.Position += component->Body.Velocity;

        bucketTree.AddEntity(component->Body.GetRoughAabb().MinCoordinate(), component->Body.GetRoughAabb().MaxCoordinate(), entityId);
    }
}
