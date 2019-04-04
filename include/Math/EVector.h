#ifndef EVECTOR_H
#define EVECTOR_H

#include "FixedPointInt.h"
#include <vector>
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
        EVector operator *(const FixedPointInt& rhs);
        EVector operator /(const FixedPointInt& rhs); // todo:
        EVector operator /(const EVector& rhs); // todo:

        // Self modification operators
        EVector& operator -=(const EVector& rhs);
        EVector& operator +=(const EVector& rhs);


        // Boolean operators
        bool operator ==(const EVector& rhs) const;
        bool operator !=(const EVector& rhs) const;

        // GT && LT operators based on which is closest towards origin
        bool operator <(const EVector& rhs) const;
        bool operator >(const EVector& rhs) const;
        bool operator >=(const EVector& rhs) const;
        bool operator <=(const EVector& rhs) const;

        // Math functions
        FixedPointInt dot(const EVector& rhs);
        FixedPointInt magnitude();

        class Projection{
        public:
            FixedPointInt Min;
            FixedPointInt Max;
        };

        Projection project(std::vector<EVector> points); // project the given points onto the vector

        void Normalize();
};


}


#endif // EVECTOR_H
