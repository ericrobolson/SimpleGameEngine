#ifndef MATERIAL_H
#define MATERIAL_H

#include "FixedPointInt.h"
using namespace SGE_Math;

namespace SGE_Physics{
    class MaterialData
    {
        public:
            MaterialData();
            virtual ~MaterialData();

            FixedPointInt Density;
            FixedPointInt Restitution;
    };
}

#endif // MATERIAL_H
