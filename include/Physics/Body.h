#ifndef BODY_H
#define BODY_H

#include "Physics/MaterialData.h"
#include "Physics/MassData.h"
#include "TransformData.h"
#include "FixedPointInt.h"
#include "EVector.h"
using namespace SGE_Math;

namespace SGE_Physics{
    class Body
    {
        public:
            Body();
            virtual ~Body();

            //todo: need a shape

            TransformData Transform;

            MaterialData Material;
            MassData Mass;

            EVector Velocity;
            EVector Force;

            FixedPointInt GravityScale;

        protected:

        private:
    };

}

#endif // BODY_H
