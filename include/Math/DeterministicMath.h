#ifndef DETERMINISTICMATH_H
#define DETERMINISTICMATH_H

namespace SGE_Math{


class FixedPointInt{
    public:
        FixedPointInt();
        //todo: add constructors for ints, floats, and other fps

        virtual ~FixedPointInt();

        // contains 2 decimal places?

        int Value;

        // Type casting
        operator float() const;
        operator int() const;

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



class DeterministicMath
{
    public:
        DeterministicMath();
        virtual ~DeterministicMath();

    protected:

    private:
};





}


#endif // DETERMINISTICMATH_H
