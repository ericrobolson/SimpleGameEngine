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

            enum MaterialType{
                Rock,
                Wood,
                Metal,
                BouncyBall,
                SuperBall,
                Pillow,
                StaticObject
            };

            void SetMaterialType(MaterialType mType);

            FixedPointInt Density;
            FixedPointInt Restitution;

            FixedPointInt Friction; // the friction to apply
    };
}

#endif // MATERIAL_H
