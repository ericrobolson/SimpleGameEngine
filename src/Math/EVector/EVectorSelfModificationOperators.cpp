#include "EVector.h"
using namespace SGE_Math;

EVector& EVector::operator -=(const EVector& rhs){
    this->X = this->X - rhs.X;
    this->Y = this->Y - rhs.Y;

    return *this;
}

EVector& EVector::operator +=(const EVector& rhs){
    this->X = this->X + rhs.X;
    this->Y = this->Y + rhs.Y;

    return *this;
}

