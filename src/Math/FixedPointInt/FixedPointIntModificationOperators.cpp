#include "FixedPointInt.h"
using namespace SGE_Math;

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

    int s;
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

    int s;
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

//todo: test this
FixedPointInt FixedPointInt::operator *(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp.Value += this->Value;

    int s;
    if (__builtin_mul_overflow(fp.Value, rhs.Value, &s)){
        fp.Value = MAXVALUE;
    } else if(__builtin_mul_overflow(fp.Value, -rhs.Value, &s)){
        fp.Value = MINVALUE;
    }
    else{
        fp.Value *= rhs.Value;
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

    fp = *this;
    fp *= rhs;

    return fp;
}

//todo: test this
FixedPointInt FixedPointInt::operator %(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp = *this;
    fp *= rhs;

    return fp;
}


//todo: test this
FixedPointInt FixedPointInt::operator ^(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp = *this;
    fp *= rhs;

    return fp;
}
