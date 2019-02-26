#ifndef EVECTOR_H
#define EVECTOR_H

#include "FixedPointInt.h"

/// Euclidean Vector

namespace SGE_Math{
class EVector
{
    public:
        // Constructors
        EVector();
        EVector(const EVector& e);
        virtual ~EVector();

        // Data fields
        FixedPointInt X;
        FixedPointInt Y;

        // Assignment operators
        EVector& operator =(const EVector& rhs);

        // Modification operators
        EVector operator -();

        EVector operator -(const EVector& rhs);
        EVector operator +(const EVector& rhs);

        // Self modification operators
        EVector& operator -=(const EVector& rhs);
        EVector& operator +=(const EVector& rhs);

        // Boolean operators
        bool operator <(const EVector& rhs) const;
        bool operator <=(const EVector& rhs) const;
        bool operator >(const EVector& rhs) const;
        bool operator >=(const EVector& rhs) const;
        bool operator ==(const EVector& rhs) const;
        bool operator !=(const EVector& rhs) const;

        // Math functions
        FixedPointInt dot(const EVector& rhs);
        FixedPointInt crossProduct(const EVector& rhs);
        FixedPointInt length(const EVector& rhs);
};


}


#endif // EVECTOR_H
