#include "FixedPointInt.h"
using namespace SGE_Math;
#include <cstring>

//todo: replace with bitwise operations
//todo: ensure all casts are deterministic, may mean writing your own

FixedPointInt::FixedPointInt()
{
    //ctor
    Value = 0;
}

FixedPointInt::FixedPointInt(double d)
{
    float f = d;
    Value = f;
}

FixedPointInt::FixedPointInt(int i)
{
    *this = i;
}


FixedPointInt::FixedPointInt(float f)
{
    *this = f;
}

FixedPointInt::~FixedPointInt()
{
    //dtor
}

// Operators
void FixedPointInt::operator ++(){
    // convert to bitshifting?
    Value += _scalingFactor;
}

void FixedPointInt::operator --(){
    // convert to bitshifting?
    Value -= _scalingFactor;
}

// Assignment operators
/*
FixedPointInt& FixedPointInt::operator =(const int& rhs){
    this->Value = rhs * this->_scalingFactor;
    return *this;
}


float my_ceiling(float f)
{
    unsigned input;
    memcpy(&input, &f, 4);
    int exponent = ((input >> 23) & 255) - 127;
    if (exponent < 0) return (f > 0);
    // small numbers get rounded to 0 or 1, depending on their sign

    int fractional_bits = 23 - exponent;
    if (fractional_bits <= 0) return f;
    // numbers without fractional bits are mapped to themselves

    unsigned integral_mask = 0xffffffff << fractional_bits;
    unsigned output = input & integral_mask;
    // round the number down by masking out the fractional bits

    memcpy(&f, &output, 4);
    if (f > 0 && output != input) ++f;
    // positive numbers need to be rounded up, not down

    return f;
}

FixedPointInt& FixedPointInt::operator =(const float& rhs){

    bool positiveValue = rhs >= 0;

    // get the absolute value of Value
    float i = rhs;

    if (!positiveValue){
        i *= -1;
    }

    // figure out rounding value
    i = i * _scalingFactor;

    float j = my_ceiling(i);

    // round
    if (i >= j){

    }

    if (!positiveValue){
        j *= -1;
    }

    this->Value = j;
    return *this;
}
*/

//todo: test this
FixedPointInt FixedPointInt::operator -(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp += *this;
    fp -= rhs;

    return fp;
}


//todo: test this
FixedPointInt FixedPointInt::operator +(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp += *this;
    fp += rhs;

    return fp;
}

//todo: test this
FixedPointInt FixedPointInt::operator *(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp = *this;
    fp *= rhs;

    return fp;
}


FixedPointInt& FixedPointInt::operator =(const FixedPointInt& rhs){
    if (this != &rhs){
        this->Value = rhs.Value;
    }

    return *this;
}


///todo: This is a key part to get right; need to ensure rounding errors are taken care of


FixedPointInt& FixedPointInt::operator +=(const FixedPointInt& rhs){
    this->Value += rhs.Value;

    return *this;
}


FixedPointInt& FixedPointInt::operator *=(const FixedPointInt& rhs){
    this->Value *= rhs.Value;
    this->Value /= _scalingFactor; // rounding issues?

    return *this;
}

FixedPointInt& FixedPointInt::operator -=(const FixedPointInt& rhs){
    this->Value -= rhs.Value;

    return *this;
}


// Type casting

FixedPointInt::operator float() const{
    return ((float)Value / _scalingFactor);
}

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

    // round up if needed
    if (remainder >= _halfScalingFactor){
        i += 1;
    }

    if (!positiveValue){
        i *= -1;
    }

    return i;
}
