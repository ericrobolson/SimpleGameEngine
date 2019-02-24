#include "FixedPointInt.h"
using namespace SGE_Math;

FixedPointInt::operator int() const{
    bool positiveValue = Value >= 0;

    // get the absolute value of Value
    int i = Value;

    if (!positiveValue){
        i *= -1;
    }

    int remainder = i % _scalingFactor;

    // get rid of bits that will be rounded
    i -= remainder;

    // convert to int representation
    i = i / _scalingFactor;

    // round up if needed; note: this is based on a 2 decimal place system, if that changes need to update this and reevaluate it

    // round up least significant decimal place
    int remainder2 = remainder % _valuesPerDecimal;
    if (remainder2 >= (_halfScalingFactor / _valuesPerDecimal)){
        remainder += (_valuesPerDecimal - remainder2);
    }

    if (remainder >= _halfScalingFactor){
        i += 1;
    }

    if (!positiveValue){
        i *= -1;
    }

    return i;
}
