#ifndef COLLISIONDECTECTOR_H
#define COLLISIONDECTECTOR_H

#include "Aabb.h"
#include "Physics/Circle.h"
#include "EVector.h"
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

        static bool CircleVsCircle(CollisionData& cd);
        static bool AabbVsAabb(CollisionData& cd);
        static bool AabbVsAabb2(CollisionData& cd, Aabb aabb1, Aabb aabb2, SGE_Math::EVector entity1Position, SGE_Math::EVector entity2Position);
        static bool AabbVsCircle(CollisionData& cd);
        static bool AabbVsAabb(EVector& positionA, EVector& positionB, Aabb abox, Aabb bbox, EVector& normal, FixedPointInt& penetration);


        static bool CheckCollision(CollisionData& cd);

    protected:

    private:
};

}

#endif // COLLISIONDECTECTOR_H
