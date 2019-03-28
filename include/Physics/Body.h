#ifndef BODY_H
#define BODY_H

#include "Physics/MaterialData.h"
#include "Physics/MassData.h"
#include "TransformData.h"
#include "FixedPointInt.h"
#include "EVector.h"
#include "ShapeData.h"
#include "Aabb.h"

#include "Physics/Constants.h"
using namespace SGE_Math;

namespace SGE_Physics{
    class Body
    {
        public:
            Body();
            virtual ~Body();

            void Initialize(MaterialData::MaterialType mType, EVector position, Aabb aabb){
                Transform.Position = position;

                // Set material data
                Material.SetMaterialType(mType);

                // Set shape
                // note: assuming aabbs are the only type right now
                Shape.SetAabb(aabb);

                // Calculate mass
                FixedPointInt mass = Material.Density * Shape.GetVolume();
                Mass.Mass = mass / Constants::GetMeterRatio();// / PhysicsScale;
                Mass.InverseMass(); // precalculate inv mass
                IsStaticObject = false;
            };

            ShapeData Shape;

            Aabb GetRoughAabb();

            TransformData Transform;

            MaterialData Material;
            MassData Mass;

            EVector Velocity;
            EVector Force;

            FixedPointInt GravityScale = 1.0_fp;

            bool IsStaticObject = false;

        protected:

        private:
    };

}

#endif // BODY_H
