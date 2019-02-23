#include "FixedPointInt.h"
using namespace SGE_Math;

bool FixedPointInt::operator >=(const FixedPointInt& rhs) const{
    return (this->Value >= rhs.Value);
}

bool FixedPointInt::operator <=(const FixedPointInt& rhs) const{
    return (this->Value <= rhs.Value);
}

bool FixedPointInt::operator >(const FixedPointInt& rhs) const{
    return (this->Value > rhs.Value);
}

bool FixedPointInt::operator <(const FixedPointInt& rhs) const{
    return (this->Value < rhs.Value);
}

bool FixedPointInt::operator ==(const FixedPointInt& rhs) const{
    return (this->Value == rhs.Value);
}

