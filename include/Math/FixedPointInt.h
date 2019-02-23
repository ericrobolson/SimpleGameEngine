#ifndef FIXEDPOINTINT_H
#define FIXEDPOINTINT_H


namespace SGE_Math{

class FixedPointInt{
    public:
        FixedPointInt();
        FixedPointInt(double d);
        FixedPointInt(float f);
        FixedPointInt(int i);
        //todo: add constructors for ints, floats, and other fps

        virtual ~FixedPointInt();

        // contains 2 decimal places?

        int Value;

        // Type casting
        operator float() const;
        operator int() const;

        // Assignment operators
        FixedPointInt& operator =(const FixedPointInt& rhs);

        // Modification operators
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

    private:
        const int _decimalPlaces = 2;
        const int _valuesPerDecimal = 10;
        const int _scalingFactor = _valuesPerDecimal * _valuesPerDecimal; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them
        const int _halfScalingFactor = _scalingFactor/2;



};
}
#endif // FIXEDPOINTINT_H
