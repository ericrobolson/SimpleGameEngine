#include "FixedPointInt.h"
using namespace SGE_Math;

#include <cstdint>


// for referencing buffer overflow checks:
// https://stackoverflow.com/a/1514309
// https://stackoverflow.com/a/20956705



FixedPointInt FixedPointInt::operator -(){
    FixedPointInt fp;
    fp.Value -= this->Value;

    return fp;
}

FixedPointInt FixedPointInt::operator -(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp.Value = this->Value;

    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    //todo: refactor so don't need to typecast?
    int_fast64_t i = (int_fast64_t)fp.Value - (int_fast64_t)rhs.Value;

    // Overflow check
    if (i >= MAXVALUE){
        fp.Value = MAXVALUE;
    }
    else if (i <= MINVALUE){
        i = MINVALUE;
    }
    else{
        fp.Value = i;
    }

    return fp;
}

FixedPointInt FixedPointInt::operator +(const FixedPointInt& rhs){

    FixedPointInt fp;

    fp.Value = this->Value;

    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    //todo: refactor so don't need to typecast?
    int_fast64_t i = (int_fast64_t)fp.Value + (int_fast64_t)rhs.Value;

    // Overflow check
    if (i >= MAXVALUE){
        fp.Value = MAXVALUE;
    }
    else if (i <= MINVALUE){
        i = MINVALUE;
    }
    else{
        fp.Value = i;
    }

    return fp;
   /*
    FixedPointInt fp;
    fp.Value += this->Value;

    int_fast32_t s;
    if (__builtin_add_overflow(fp.Value, rhs.Value, &s)){
        if (fp.Value < 0 && rhs.Value < 0){
            fp.Value = MINVALUE;
        }else{
            fp.Value = MAXVALUE;
        }
    } else if (__builtin_sub_overflow(fp.Value, rhs.Value, &s)){
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
    */
}

//todo: test this
FixedPointInt FixedPointInt::operator *(const FixedPointInt& rhs){
    FixedPointInt fp;

    if (this->Value == 0 || rhs.Value == 0){
        return fp;
    }

    bool isNegative = (this->Value > 0 && rhs.Value < 0 || this->Value < 0 && rhs.Value > 0);


    int_fast64_t v1 = this->Value;
    int_fast64_t v2 = rhs.Value;

    if (v1 < 0){
        v1 *= -1;
    }

    if (v2 < 0){
        v2 *= -1;
    }


    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    int_fast64_t i = v1 * v2;

    // convert it to FixedPointInt value format, rounding decimals
    // template this?


    // Overflow check
    if (i >= ((int_fast64_t)MAXVALUE * (int_fast64_t)_scalingFactor)){
        if (isNegative){
            fp.Value = MINVALUE;
        }else{
            fp.Value = MAXVALUE;
        }
    }
    else{
            for (int j = 0; j < _decimalPlaces; j++){
        int_fast64_t remainder = i % _valuesPerDecimal;

        // shift it
        i -= remainder;
        i = i / _valuesPerDecimal;

        // round up
        if (remainder >= _valuesPerDecimal / 2){
            i += 1;
        }
    }

        fp.Value = i;

        if (isNegative){
            fp.Value *= -1;
        }
    }




    return fp;
}



//todo: test this
// reference; https://gamedev.stackexchange.com/a/112547
FixedPointInt FixedPointInt::operator /(const FixedPointInt& rhs){
    FixedPointInt fp;

    // possible edge cases: max int / 1
    // min int / -1
    // min int / 1
    // max int / -1

    // check dividing by zero cases
    if (this->Value == 0){
        return fp;
    }
    else if (rhs.Value == 0){
        if (this->Value > 0){
            fp.Value = MAXVALUE;
        }else{
            fp.Value = MINVALUE;
        }

        return fp;
    }

    fp.Value = this->Value;

    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    int_fast64_t i = ((int_fast64_t)fp.Value * _scalingFactor * _scalingFactor) / (int_fast64_t)rhs.Value;

    // convert it to FixedPointInt value format, rounding decimals
    // template this?
    for (int j = 0; j < _decimalPlaces; j++){
        int_fast64_t remainder = i % _valuesPerDecimal;

        // shift it
        i -= remainder;
        i = i / _valuesPerDecimal;

        // round up
        if (remainder >= _valuesPerDecimal / 2){
            i += 1;
        }
    }

    // Overflow check
    if (i >= MAXVALUE){
        fp.Value = MAXVALUE;
    }
    else if (i <= MINVALUE){
        fp.Value = MINVALUE;
    }
    else{
        fp.Value = i;
    }

    return fp;
}
