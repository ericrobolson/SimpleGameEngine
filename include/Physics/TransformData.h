#ifndef TRANSFORMDATA_H
#define TRANSFORMDATA_H
#include "Coordinate.h"
#include "FixedPointInt.h"
using namespace SGE_Math;

namespace SGE_Physics{
class TransformData
{
    public:
        TransformData();
        virtual ~TransformData();

        Coordinate Coordinates;
        FixedPointInt Radians;

    protected:

    private:
};

}

#endif // TRANSFORMDATA_H
