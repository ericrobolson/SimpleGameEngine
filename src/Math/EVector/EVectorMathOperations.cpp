#include "EVector.h"
using namespace SGE_Math;

FixedPointInt EVector::dot(const EVector& rhs){
    FixedPointInt fp;

    fp = this->X * rhs.X + this->Y * rhs.Y;

    return fp;
}

FixedPointInt EVector::magnitude(){
    //todo: test
    FixedPointInt fp;
    fp = (X * X + Y * Y).sqrt();
    return fp;
}


void EVector::Normalize(){
    //todo: test

    EVector vec = *this / magnitude();
    X = vec.X;
    Y = vec.Y;
}
