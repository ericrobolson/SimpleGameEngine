#ifndef COLLISIONDECTECTOR_H
#define COLLISIONDECTECTOR_H

#include "Aabb.h"
#include "Physics/Circle.h"
#include "CollisionData.h"
#include <memory>

namespace SGE_Physics{
class CollisionDectector
{
    public:
        CollisionDectector();
        virtual ~CollisionDectector();

        static bool AabbVsAabb(Aabb a,Aabb b);

        static bool CircleVsCircle(Circle a, Circle b);

        static bool CircleVsCircle(std::shared_ptr<CollisionData> cd);
        static bool AabbVsAabb(std::shared_ptr<CollisionData> cd);
        static bool AabbVsCircle(std::shared_ptr<CollisionData> cd);

        static bool CheckCollision(std::shared_ptr<CollisionData> cd);

    protected:

    private:
};

}

#endif // COLLISIONDECTECTOR_H
