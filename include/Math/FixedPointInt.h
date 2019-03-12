#ifndef FIXEDPOINTINT_H
#define FIXEDPOINTINT_H

#include <limits>
#include <cstdint>

namespace SGE_Math{

class FixedPointInt{
    public:
        // Constructors
        FixedPointInt();
        FixedPointInt(const FixedPointInt& fp);

        virtual ~FixedPointInt();

        // contains 2 decimal places?

        int_fast32_t Value;

        // Type casting
        explicit operator int() const;

        // Assignment operators
        FixedPointInt& operator =(const FixedPointInt& rhs);

        // Modification operators
        FixedPointInt operator -();

        FixedPointInt operator -(const FixedPointInt& rhs);
        FixedPointInt operator +(const FixedPointInt& rhs);
        FixedPointInt operator *(const FixedPointInt& rhs);
        FixedPointInt operator /(const FixedPointInt& rhs);
        FixedPointInt operator /(const int& rhs);

        // Self modification operators
        FixedPointInt& operator +=(const FixedPointInt& rhs);
        FixedPointInt& operator -=(const FixedPointInt& rhs);
        FixedPointInt& operator *=(const FixedPointInt& rhs);
        FixedPointInt& operator /=(const FixedPointInt& rhs);
        void operator ++();
        void operator --();

        // Boolean operators
        bool operator <(const FixedPointInt& rhs) const;
        bool operator <=(const FixedPointInt& rhs) const;
        bool operator >(const FixedPointInt& rhs) const;
        bool operator >=(const FixedPointInt& rhs) const;
        bool operator ==(const FixedPointInt& rhs) const;
        bool operator !=(const FixedPointInt& rhs) const;

        // Mathematical operations
        FixedPointInt abs();
        FixedPointInt sqrt();

        void SetValueFromDouble(const long double& rhs);

        // todo: reference these through a static "Constants" class for optimization
        const int_fast32_t MINVALUE = std::numeric_limits<int>::min(); // Minimum allowed integer value
        const int_fast32_t MAXVALUE = std::numeric_limits<int>::max(); // Maximum allowed integer value

    private:
        // todo: reference these through a static "Constants" class for optimization

        const int_fast32_t _decimalPlaces = 2;
        const int_fast32_t _valuesPerDecimal = 10;
        const int_fast32_t _scalingFactor = _valuesPerDecimal * _valuesPerDecimal; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them
        const int_fast32_t _halfScalingFactor = _scalingFactor/2;

        const int_fast32_t MININTVALUE= std::numeric_limits<int_fast32_t>::min() / _scalingFactor; // Minimum allowed integer value
        const int_fast32_t MAXINTVALUE = std::numeric_limits<int_fast32_t>::max() / _scalingFactor;; // Maximum allowed integer value
};
}

SGE_Math::FixedPointInt operator"" _fp(long double d);

#endif // FIXEDPOINTINT_H
