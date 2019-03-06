#ifndef TRANSFORMDATA_H
#define TRANSFORMDATA_H
#include "FixedPointInt.h"
#include "EVector.h"
using namespace SGE_Math;

namespace SGE_Physics{
class TransformData
{
    public:
        TransformData();
        virtual ~TransformData();

        EVector Position;
        FixedPointInt Radians;

    protected:

    private:
};

}

#endif // TRANSFORMDATA_H
