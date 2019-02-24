#ifndef COORDINATE_H
#define COORDINATE_H

#include "FixedPointInt.h"
using namespace SGE_Math;

namespace SGE_Physics{
class Coordinate
{
    public:
        Coordinate();
        virtual ~Coordinate();

        FixedPointInt X;
        FixedPointInt Y;

    protected:

    private:
};

}

#endif // COORDINATE_H
