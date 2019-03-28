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
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();

        void UpdatePhysics(FixedPointInt hz, ECS::EntityComponentManager &ecs, BucketTree& bucketTree);

        void ResolveCollision(CollisionData& cd);
    private:
        FixedPointInt _totalMassInSystem;
};
}

#endif // PHYSICSENGINE_H
