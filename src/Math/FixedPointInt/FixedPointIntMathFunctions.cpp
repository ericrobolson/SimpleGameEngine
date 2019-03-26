#include "FixedPointInt.h"
using namespace SGE_Math;

FixedPointInt FixedPointInt::abs(){
    FixedPointInt fp;

    fp.Value = this->Value;

    if (fp.Value < 0){
        fp = -fp;
    }

    return fp;
}


FixedPointInt FixedPointInt::sqrt(){
    FixedPointInt fp;

    fp.Value = this->Value;

    //todo: sqrt it; possibly use lookup table?
    //todo: need to implement

    return fp;
}


FixedPointInt& FixedPointInt::maximum(FixedPointInt& a, FixedPointInt& b){
    if (a.Value >= b.Value){
        return a;
    }

    return b;
}

FixedPointInt& FixedPointInt::minimum(FixedPointInt& a, FixedPointInt& b){
    if (a.Value <= b.Value){
        return a;
    }

    return b;
}
