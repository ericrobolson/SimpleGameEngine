#ifndef EVECTOR_H
#define EVECTOR_H

#include "FixedPointInt.h"

/// Euclidean Vector

namespace SGE_Math{
class EVector
{
    public:
        EVector();
        EVector(const EVector& e);
        virtual ~EVector();

        FixedPointInt X;
        FixedPointInt Y;

        EVector& operator =(const EVector& rhs);


        EVector& operator -(const EVector& rhs);
        EVector& operator *(const EVector& rhs);
        EVector& operator +(const EVector& rhs);
        EVector& operator /(const EVector& rhs);

        FixedPointInt& dot(const EVector& rhs);
        FixedPointInt& length(const EVector& rhs);

        // Boolean operators
        bool operator <(const EVector& rhs) const;
        bool operator <=(const EVector& rhs) const;
        bool operator >(const EVector& rhs) const;
        bool operator >=(const EVector& rhs) const;
        bool operator ==(const EVector& rhs) const;
        bool operator !=(const EVector& rhs) const;




    protected:

    private:
};


}


#endif // EVECTOR_H
