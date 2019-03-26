#include "FixedPointInt.h"
using namespace SGE_Math;

FixedPointInt::operator int() const{
    bool positiveValue = Value >= 0;

    int_fast32_t i = Value;

    if (!positiveValue){
        i = -i;
    }

    // round up decimal places
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

    if (!positiveValue){
        i *= -1;
    }

    return i;
}

FixedPointInt::operator std::string() const{
    std::string s = std::to_string(Value);

    // pad with leading 0's
    while (s.size() <= 2){
        s.insert(0, "0");
    }

    // insert decimal
    s.insert(s.size() -2, ".");

    return s;
}
