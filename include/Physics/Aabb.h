#ifndef AABB_H
#define AABB_H

#include "Vect2.h"
#include "Coordinate.h"

#include "FixedPointInt.h"
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

            Coordinate MinCoordinate();
            Coordinate MaxCoordinate();

            FixedPointInt HalfWidth;
            FixedPointInt HalfHeight;
            Vect2 Position;

        protected:

        private:
    };

}


#endif // AABB_H
