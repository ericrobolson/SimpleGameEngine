#include "EVector.h"
using namespace SGE_Math;

EVector& EVector::operator =(const EVector& rhs){
    if (this != &rhs){
        this->X = rhs.X;
        this->Y = rhs.Y;
    }

    return *this;
}
