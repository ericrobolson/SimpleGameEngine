#include "FixedPointInt.h"
using namespace SGE_Math;
#include <string>


#include <sstream>

//todo: replace with bitwise operations
//todo: ensure all casts are deterministic, may mean writing your own


FixedPointInt operator"" _fp(long double d){
    FixedPointInt fp;

    fp.SetValueFromDouble(d);

    return fp;
}


FixedPointInt::FixedPointInt()
{
    Value = 0;
}

FixedPointInt::FixedPointInt(const FixedPointInt& fp)
{
    Value = fp.Value;
}

FixedPointInt::~FixedPointInt()
{
    //dtor
}

//todo: test
void FixedPointInt::SetValueFromDouble(const long double& rhs){
    long double d = rhs * _scalingFactor;

    bool isNegative = d < 0;

    // get absolute value
    if (isNegative){
        d = -d;
    }

    /*
    long double decimalRemainder = d % 1; // need to convert to str?

    if (decimalRemainder != 0){
        // remove decimals
        d -= decimalRemainder;

        // round decimalRemainder to see if we need to round up d
        // first, convert to int and remove decimal places
        int decimalsShifted = 1;
        while (decimalRemainder % 1 != 0){
            decimalRemainder *= 10;
            i++;
        }

        // round up the number
        for (int i = 0; i < decimalsShifted; i++){
            int j = decimalRemainder % 10;

            // remove remainder
            decimalRemainder -= j;

            // shift
            decimalRemainder /= 10;

            if (decimalRemainder >= (_halfScalingFactor * _valuesPerDecimal)/_scalingFactor)){
                decimalRemainder += 1;
            }
        }

        // round up d
        if (decimalRemainder >= (_halfScalingFactor * _valuesPerDecimal)/_scalingFactor)){
            d += 1;
        }
    }
*/
    if (isNegative){
        d = -d;
    }

    Value = d;
}
