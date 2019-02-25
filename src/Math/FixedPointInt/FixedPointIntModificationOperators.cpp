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

    fp.Value = this->Value;

    if (fp.Value < 0){
        fp.Value *= -1;
    }

    int absRhs = rhs.Value;
    if (absRhs < 0){
        absRhs *= -1;
    }


    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    int_fast64_t i = (int_fast64_t)fp.Value * (int_fast64_t)absRhs;

    // convert it to FixedPointInt value format, rounding decimals
    // template this?
    for (int j = 0; j < _decimalPlaces; j++){
        int_fast32_t remainder = i % _valuesPerDecimal;

        // shift it
        i -= remainder;
        i = i / _valuesPerDecimal;

        // round up
        if (remainder >= _valuesPerDecimal / 2){
            i += 1;
        }
    }

    if (isNegative){
        i *= -1;
    }

    // Overflow check
    if (i >= MAXVALUE){
        fp.Value = MAXVALUE;
    } if (i <= MINVALUE){
        fp.Value = MINVALUE;
    }
    else{
        fp.Value = i;
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

    bool finalValueIsNegative = this->Value < 0 && rhs.Value > 0 || this->Value > 0 && rhs.Value < 0;

    fp.Value = this->Value;

    // Convert fp to positive, as we'll flip the signs later on
    if (fp.Value < 0){
        fp.Value *= -1;
    }

    int_fast32_t absRhsValue = rhs.Value;
    if (absRhsValue < 0){
        absRhsValue *= -1;
    }

    // Typecast to a bigger format, so if it's a valid value an overflow will not occur
    int_fast64_t i = ((int_fast64_t)fp.Value * _scalingFactor * _scalingFactor) / (int_fast64_t)absRhsValue;

    // convert it to FixedPointInt value format, rounding decimals
    // template this?
    for (int j = 0; j < _decimalPlaces; j++){
        int_fast32_t remainder = i % _valuesPerDecimal;

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
    else{
        fp.Value = i;
    }

    if (finalValueIsNegative){
        fp.Value *= -1;
    }

    return fp;
}
