#ifndef AABB_H
#define AABB_H

#include "Vect2.h"
#include "Coordinate.h"

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

            int HalfWidth;
            int HalfHeight;
            Vect2 Position;

        protected:

        private:
    };

}


#endif // AABB_H
