#include "DeterministicMath.h"
using namespace SGE_Math;


FixedPointInt::FixedPointInt()
{
    //ctor
    _value = 0;
}

FixedPointInt::~FixedPointInt()
{
    //dtor
}

// Operators
void FixedPointInt::operator ++(){
    // convert to bitshifting?
    _value += _scalingFactor;
}

void FixedPointInt::operator --(){
    // convert to bitshifting?
    _value -= _scalingFactor;
}


// Type casting
FixedPointInt::operator float() const{
    return ((float)_value / _scalingFactor);
}

FixedPointInt::operator int() const{
     int halfScalingFactor = _scalingFactor/2;

    int remainder = _value % _scalingFactor;

    // If no remainder, then return the value as there's no decimal places
    if (remainder == 0){
        return (int)(_value / _scalingFactor);
    }
    // Round up if remainder is greater than half the scaling value
    else if (remainder > halfScalingFactor){
        // Figure out how much to round up by to make it evenly divisible
        int difference = _scalingFactor - remainder;

        // Then add the difference to round by to the value so it's easily divisible, divide by scalingFactor, cast to an int and return
        return (int)(((_value + difference))/_scalingFactor);
    }
    // Round down
    else{
        // Subtract the remainder to make it evenly divisible
        return (int)((_value - remainder)/_scalingFactor);
    }
}

DeterministicMath::DeterministicMath()
{
    //ctor
}

DeterministicMath::~DeterministicMath()
{
    //dtor
}
