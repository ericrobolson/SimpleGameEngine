#ifndef CIRCLE_H
#define CIRCLE_H

#include "FixedPointInt.h"
#include "EVector.h"
using namespace SGE_Math;

namespace SGE_Physics{

    /// Circle
    /// A shape that represents a circular body
    class Circle
    {
        public:
            Circle();
            virtual ~Circle();

            FixedPointInt Radius;
            EVector Position;


        protected:

        private:
    };


}

#endif // CIRCLE_H
