#ifndef BODY_H
#define BODY_H

#include "Physics/MaterialData.h"
#include "Physics/MassData.h"
#include "TransformData.h"
#include "FixedPointInt.h"
#include "EVector.h"
#include "ShapeData.h"
#include "Aabb.h"
using namespace SGE_Math;

namespace SGE_Physics{
    class Body
    {
        public:
            Body();
            virtual ~Body();

            ShapeData Shape;

            Aabb GetRoughAabb();

            TransformData Transform;

            MaterialData Material;
            MassData Mass;

            EVector Velocity;
            EVector Force;

            FixedPointInt GravityScale = 1.0_fp;

        protected:

        private:
    };

}

#endif // BODY_H
