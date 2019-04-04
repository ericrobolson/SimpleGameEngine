#include "FixedPointInt.h"

#include <cmath>
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
    if (this->Value <= 0){
        return 0.0_fp;
    }

    FixedPointInt fp = *this;// / 4.0_fp;

    long double i = fp.Value / _scalingFactor;

    fp.SetValueFromDouble(std::sqrt(i));

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
