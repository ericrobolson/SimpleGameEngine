#ifndef FIXEDPOINTINT_H
#define FIXEDPOINTINT_H

#include <limits>


namespace SGE_Math{

class FixedPointInt{
    public:
        // Constructors
        FixedPointInt();
        FixedPointInt(const FixedPointInt& fp);

        virtual ~FixedPointInt();

        // contains 2 decimal places?

        int Value;

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
        FixedPointInt operator %(const FixedPointInt& rhs);
        FixedPointInt operator ^(const FixedPointInt& rhs);

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


        void SetValueFromDouble(const long double& rhs);


    private:
        const int _decimalPlaces = 2;
        const int _valuesPerDecimal = 10;
        const int _scalingFactor = _valuesPerDecimal * _valuesPerDecimal; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them
        const int _halfScalingFactor = _scalingFactor/2;

        const int MINVALUE = std::numeric_limits<int>::min(); // Minimum allowed integer value
        const int MAXVALUE = std::numeric_limits<int>::max(); // Maximum allowed integer value

        const int MININTVALUE= std::numeric_limits<int>::min() / _scalingFactor; // Minimum allowed integer value
        const int MAXINTVALUE = std::numeric_limits<int>::max() / _scalingFactor;; // Maximum allowed integer value

        void SetValueFromInt(const int& rhs);
};
}

SGE_Math::FixedPointInt operator"" _fp(long double d);

#endif // FIXEDPOINTINT_H
