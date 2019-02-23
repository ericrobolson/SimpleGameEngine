#ifndef COLLISIONDECTECTOR_H
#define COLLISIONDECTECTOR_H

#include "Aabb.h"
#include "Physics/Circle.h"

namespace SGE_Physics{
class CollisionDectector
{
    public:
        CollisionDectector();
        virtual ~CollisionDectector();

        static bool AabbVsAabb(Aabb a,Aabb b);

        static bool CircleVsCircle(Circle a, Circle b);

    protected:

    private:
};

}

#endif // COLLISIONDECTECTOR_H
