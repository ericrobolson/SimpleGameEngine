#ifndef DETERMINISTICMATH_H
#define DETERMINISTICMATH_H

namespace SGE_Math{


class FixedPointInt{
    public:
        FixedPointInt();
        virtual ~FixedPointInt();

        // contains 2 decimal places?

        float ToFloat();
        int ToInt();

        // Type casting
        operator float() const;
        operator int() const;

        // Operators
        void operator ++();
        void operator --();
        // +=
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
        const int _scalingFactor = 10 * 10; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them



        int _value;

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
