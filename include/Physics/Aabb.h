#ifndef AABB_H
#define AABB_H

#include "FixedPointInt.h"
#include "EVector.h"
using namespace SGE_Math;

namespace SGE_Physics
{
    /// Axis Aligned Bounding Box
    /// Used for non-circular, rectangle shapes
    class Aabb
    {
        public:
            Aabb();
            virtual ~Aabb();

            EVector MinCoordinate();
            EVector MaxCoordinate();

            FixedPointInt HalfWidth;
            FixedPointInt HalfHeight;
            EVector Position;

        protected:

        private:
    };

}


#endif // AABB_H
