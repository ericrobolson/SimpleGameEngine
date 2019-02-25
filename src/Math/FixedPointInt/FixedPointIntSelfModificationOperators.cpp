#include "FixedPointInt.h"
using namespace SGE_Math;


// Operators
void FixedPointInt::operator ++(){
    *this = 1.0_fp + *this;
}

void FixedPointInt::operator --(){
    *this = *this - 1.0_fp;
}

FixedPointInt& FixedPointInt::operator +=(const FixedPointInt& rhs){
    *this = *this + rhs;
    return *this;
}

FixedPointInt& FixedPointInt::operator -=(const FixedPointInt& rhs){
    *this = *this - rhs;
    return *this;
}

FixedPointInt& FixedPointInt::operator /=(const FixedPointInt& rhs){
    *this = *this / rhs;
    return *this;
}


FixedPointInt& FixedPointInt::operator *=(const FixedPointInt& rhs){
    *this = *this * rhs;
    return *this;
}



