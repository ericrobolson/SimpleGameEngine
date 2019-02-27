#include "EVector.h"
using namespace SGE_Math;

FixedPointInt EVector::dot(const EVector& rhs){
    FixedPointInt fp;

    fp = this->X * rhs.X + this->Y * rhs.Y;

    return fp;

}
