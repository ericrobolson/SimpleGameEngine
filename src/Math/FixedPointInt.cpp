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

/*
FixedPointInt::FixedPointInt(const int& i)
{
    SetValueFromInt(i);
}
*/
//todo: test

FixedPointInt::~FixedPointInt()
{
    //dtor
}

// Private functions
void FixedPointInt::SetValueFromInt(const int& rhs){
    // Overflow check
    if (rhs > MAXINTVALUE){
        Value = MAXVALUE;
    }
    // Underflow check
    else if (rhs < MININTVALUE){
        Value = MINVALUE;
    }
    else{
        Value = rhs * _scalingFactor;
    }
}
/*
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
*/
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





//todo: refactor these out and test



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



//todo: test this



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
/*

// Type casting

FixedPointInt::operator float() const{
    return ((float)Value / _scalingFactor);
}


*/
