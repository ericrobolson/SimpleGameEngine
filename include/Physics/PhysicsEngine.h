#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "EntityComponentManager.h"
#include "FixedPointInt.h"
#include "CollisionData.h"
#include <memory>

using namespace SGE_Math;

namespace SGE_Physics{

class PhysicsEngine
{
    public:
        PhysicsEngine();
        virtual ~PhysicsEngine();

        void UpdatePhysics(FixedPointInt timeStep, ECS::EntityComponentManager &ecs);

        void ResolveCollision(CollisionData& cd);
    private:

};
}

#endif // PHYSICSENGINE_H
