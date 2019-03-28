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
        PhysicsEngine();
        virtual ~PhysicsEngine();

        /// Get the gravity
        static FixedPointInt GetGravity(){
            return 2.0_fp;
            return 9.81_fp;
        }

        void UpdatePhysics(FixedPointInt hz, ECS::EntityComponentManager &ecs, BucketTree& bucketTree);

        void ResolveCollision(CollisionData& cd);
    private:
        FixedPointInt _totalMassInSystem;
};
}

#endif // PHYSICSENGINE_H
