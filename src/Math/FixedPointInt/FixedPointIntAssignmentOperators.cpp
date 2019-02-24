#include "FixedPointInt.h"
using namespace SGE_Math;

FixedPointInt& FixedPointInt::operator =(const FixedPointInt& rhs){
    if (this != &rhs){
        this->Value = rhs.Value;
    }

    return *this;
}
