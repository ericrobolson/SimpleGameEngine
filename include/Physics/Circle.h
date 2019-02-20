#ifndef CIRCLE_H
#define CIRCLE_H

#include "Physics/Vect2.h"

namespace SGE_Physics{

    /// Circle
    /// A shape that represents a circular body
    class Circle
    {
        public:
            Circle();
            virtual ~Circle();

            int Radius;
            Vect2 Position;


        protected:

        private:
    };


}

#endif // CIRCLE_H
