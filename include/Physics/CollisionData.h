#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H
#include <memory>
#include "FixedPointInt.h"
#include "EVector.h"
#include "Body.h"
using namespace SGE_Math;

namespace SGE_Physics{
class CollisionData
{
    public:
        CollisionData(Body& entity1, Body& entity2);
        virtual ~CollisionData();

        Body& Entity1;
        Body& Entity2;

        FixedPointInt Penetration;
        EVector Normal;
};

}

#endif // COLLISIONDATA_H
