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

    Value = d;

    return;

    bool roundUp;
    bool isPositive = d >= (long double)0;

    // convert to absolute value for simpler math
    if (!isPositive){
        d *= -1;
    }

    // Get the decimal value:
    std::ostringstream strs;
    strs << d;

    std::string floatStr = strs.str();
    int strLen = floatStr.length();

    int i = strLen -1;

    Value = std::stod(floatStr.substr(0, floatStr.find('.')));


    // round the decimal points
    while (i >= 0){
        char c = floatStr[i];

        if (c != '.'){
                /*
            int cInt = c - '0'; // convert char to int, subtracting offset of '0' since it's sequential

            // round up the bits we can't store
            if (roundUp){
                cInt++;
                roundUp = false;
            }

            if (cInt >= 5){
                roundUp = true;
            }
            */
        }

        else{
            break;
        }

        i--;
    }


    if (roundUp){
        Value += 1;
    }

    // convert from absolute value
    if (!isPositive){
        Value *= -1;
    }
}


FixedPointInt FixedPointInt::operator -(){
    FixedPointInt fp;
    fp.Value -= this->Value;

    return fp;
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
FixedPointInt FixedPointInt::operator -(const FixedPointInt& rhs){
    FixedPointInt fp;

    fp.Value += this->Value;
    fp.Value += rhs.Value;

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
/*

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
*/
