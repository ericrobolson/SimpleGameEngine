#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "EntityComponentManager.h"
#include "FixedPointInt.h"
#include "CollisionData.h"
#include "SpatialHashMap.h"
#include <memory>
#include "BucketTree.h"

using namespace SGE_Math;

namespace SGE_Physics{

class PhysicsEngine
{
    // General rules:
    // Keep objects to a volume smaller than 15m^2, otherwise you'll run into issues.
    // Everything assumes 1 unit = 1 meter


    public:
        PhysicsEngine(){
            //_gravity.Y = 0.1_fp;
        };

        virtual ~PhysicsEngine();

        //todo: allow setting of gravity?

        /// Get the gravity
        EVector GetGravity(){
            return _gravity;
        }

        void UpdatePhysics(FixedPointInt hz, ECS::EntityComponentManager &ecs, BucketTree& bucketTree);

        void ResolveCollision(CollisionData& cd);
    private:
        EVector _gravity;
};
}

#endif // PHYSICSENGINE_H
