#include "DeterministicMath.h"
using namespace SGE_Math;


FixedPointInt::FixedPointInt()
{
    //ctor
    Value = 0;
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
FixedPointInt& FixedPointInt::operator =(const int& rhs){
    this->Value = rhs * this->_scalingFactor;
    return *this;
}

FixedPointInt& FixedPointInt::operator =(const FixedPointInt& rhs){
    if (this != &rhs){
        this->Value = rhs.Value;
    }

    return *this;
}





///todo: This is a key part to get right; need to ensure rounding errors are taken care of
FixedPointInt& FixedPointInt::operator =(const float& rhs){
    this->Value = rhs * this->_scalingFactor;
    return *this;

/*
    int halfScalingFactor = _scalingFactor/2;

    int remainder = rhs % _scalingFactor;



    // If no remainder, then return the value as there's no decimal places
    if (remainder == 0){
        return (int)(Value / _scalingFactor);
    }
    // Round up if remainder is greater than half the scaling value
    else if (remainder > halfScalingFactor){
        // Figure out how much to round up by to make it evenly divisible
        int difference = _scalingFactor - remainder;

        // Then add the difference to round by to the value so it's easily divisible, divide by scalingFactor, cast to an int and return
        return (int)(((Value + difference))/_scalingFactor);
    }
    // Round down
    else{
        // Subtract the remainder to make it evenly divisible
        return (int)((Value - remainder)/_scalingFactor);
    }
*/
}


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

DeterministicMath::DeterministicMath()
{
    //ctor
}

DeterministicMath::~DeterministicMath()
{
    //dtor
}
