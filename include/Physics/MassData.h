#ifndef MASSDATA_H
#define MASSDATA_H

#include "FixedPointInt.h"
#include <memory>
using namespace SGE_Math;

namespace SGE_Physics{
class MassData
{
    public:
        MassData();
        virtual ~MassData();

        FixedPointInt Mass;
        FixedPointInt InverseMass();

        FixedPointInt Inertia;
        FixedPointInt InverseInertia;

        bool MassIsCalculated; // As this is a storage container for Mass, need to set it based on the Shape + Density and other factors
        bool InertiaIsCalculated; //

    protected:

    private:
        std::shared_ptr<FixedPointInt> _inverseMass;
};

}

#endif // MASSDATA_H
