#include "EVector.h"
using namespace SGE_Math;

bool EVector::operator !=(const EVector& rhs) const{
    return (this->X != rhs.X || this->Y != rhs.Y);
}

bool EVector::operator ==(const EVector& rhs) const{
    return (this->X == rhs.X && this->Y == rhs.Y);
}
