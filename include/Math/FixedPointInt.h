#ifndef FIXEDPOINTINT_H
#define FIXEDPOINTINT_H


namespace SGE_Math{

class FixedPointInt{
    public:
        FixedPointInt();
        //todo: add constructors for ints, floats, and other fps

        virtual ~FixedPointInt();

        // contains 2 decimal places?

        int Value;

        // Type casting
        explicit operator float() const;
        explicit operator int() const;

        //todo: doubles?

        // Operators
        void operator ++();
        void operator --();

        FixedPointInt& operator +=(const FixedPointInt& rhs);
        FixedPointInt& operator -=(const FixedPointInt& rhs);
        FixedPointInt& operator *=(const FixedPointInt& rhs);


        FixedPointInt& operator =(const FixedPointInt& rhs);
        FixedPointInt& operator =(const float& rhs);
        FixedPointInt& operator =(const int& rhs);


        FixedPointInt operator -(const FixedPointInt& rhs);
        FixedPointInt operator +(const FixedPointInt& rhs);
        FixedPointInt operator *(const FixedPointInt& rhs);
        FixedPointInt operator /(const FixedPointInt& rhs);
        FixedPointInt operator %(const FixedPointInt& rhs);
        FixedPointInt operator ^(const FixedPointInt& rhs);

        bool operator <(const FixedPointInt& rhs) const;
        bool operator <=(const FixedPointInt& rhs) const;
        bool operator >(const FixedPointInt& rhs) const;
        bool operator >=(const FixedPointInt& rhs) const;

        bool operator ==(const FixedPointInt& rhs) const;


        // *=
        // /=
        // +
        // *
        // /
        // %
        // postfix ++
        // postfix --


    private:
        const int _decimalPlaces = 2;
        const int _valuesPerDecimal = 10;
        const int _scalingFactor = _valuesPerDecimal * _valuesPerDecimal; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them
        const int _halfScalingFactor = _scalingFactor/2;



};
}
#endif // FIXEDPOINTINT_H
