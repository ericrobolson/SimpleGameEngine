#ifndef AABB_H
#define AABB_H

#include "Vect2.h"

namespace SGE_Physics
{
    /// Axis Aligned Bounding Box
    /// Used for non-circular, rectangle shapes
    class Aabb
    {
        public:
            Aabb();
            virtual ~Aabb();

            Vect2 Min;
            Vect2 Max;

        protected:

        private:
    };

}


#endif // AABB_H
