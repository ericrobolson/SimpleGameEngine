#include "FixedPointInt.h"
using namespace SGE_Math;

#include <cstdint>


// for referencing buffer overflow checks:
// https://stackoverflow.com/a/1514309
// https://stackoverflow.com/a/20956705
//void BufferOverFlowCheck(int&)

FixedPointInt FixedPointInt::operator -(){
    FixedPointInt fp;
    fp.Value -= this->Value;

    return fp;
}

FixedPointInt FixedPointInt::operator -(const FixedPointInt& rhs){
    FixedPointInt fp;
    fp.Value += this->Value;

    int_fast32_t s;
    if (__builtin_sub_overflow(fp.Value, rhs.Value, &s)){
        fp.Value = MAXVALUE;
    } else if(__builtin_sub_overflow(fp.Value, -rhs.Value, &s)){
        fp.Value = MINVALUE;
    }
    else{
        fp.Value -= rhs.Value;
    }

    return fp;
}

FixedPointInt FixedPointInt::operator +(const FixedPointInt& rhs){
    FixedPointInt fp;
    fp.Value += this->Value;

    int_fast32_t s;
    if (__builtin_add_overflow(fp.Value, rhs.Value, &s)){
        if (fp.Value < 0 && rhs.Value < 0){
            fp.Value = MINVALUE;
        }else{
            fp.Value = MAXVALUE;
        }
    }
    else{
        fp.Value += rhs.Value;
    }

    return fp;
}


int_fast32_t Divide(int_fast32_t a, int_fast32_t b){

return a / b;
}

//todo: test this
FixedPointInt FixedPointInt::operator *(const FixedPointInt& rhs){
    FixedPointInt fp;

    if (this->Value == 0 || rhs.Value == 0){
        return fp;
    }

    bool finalValueIsNegative = this->Value < 0 && rhs.Value > 0 || this->Value > 0 && rhs.Value < 0;

    fp.Value = this->Value;

    // Convert fp to positive, as we'll flip the signs later on
    if (fp.Value < 0){
        fp.Value *= -1;
    }

    int absRhsValue = rhs.Value;
    if (absRhsValue < 0){
        absRhsValue *= -1;
    }

    int_fast32_t s;
    if (__builtin_mul_overflow(fp.Value, absRhsValue, &s)){
        // check if we can divide
        if (absRhsValue < _scalingFactor){
            int_fast64_t i = (int_fast64_t)fp.Value * absRhsValue;

            // convert it to FixedPointInt value format, rounding decimals
            // template this?
            for (int j = 0; j < _decimalPlaces; j++){
                int remainder = i % _valuesPerDecimal;

                // shift it
                i -= remainder;
                i = i / _valuesPerDecimal;

                // round up
                if (remainder >= _valuesPerDecimal / 2){
                    i += 1;
                }
            }

            fp.Value = i;
        }
        else{
            fp.Value = MAXVALUE;
        }
    }
    else{
        int i = fp.Value * absRhsValue;

        // convert it to FixedPointInt value format, rounding decimals
        // template this?
        for (int j = 0; j < _decimalPlaces; j++){
            int remainder = i % _valuesPerDecimal;

            // shift it
            i -= remainder;
            i = i / _valuesPerDecimal;

            // round up
            if (remainder >= _valuesPerDecimal / 2){
                i += 1;
            }
        }

        fp.Value = i;
    }

    if (finalValueIsNegative){
        fp.Value *= -1;
    }

    return fp;
}



//todo: test this
FixedPointInt FixedPointInt::operator /(const FixedPointInt& rhs){
    FixedPointInt fp;

    // possible edge cases: max int / 1
    // min int / -1
    // min int / 1
    // max int / -1

    fp.Value = this->Value;
    fp.Value /= rhs.Value;

    return fp;
}
