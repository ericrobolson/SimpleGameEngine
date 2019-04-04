#ifndef BODY_H
#define BODY_H

#include "Physics/MaterialData.h"
#include "Physics/MassData.h"
#include "TransformData.h"
#include "FixedPointInt.h"
#include "EVector.h"
#include "ShapeData.h"
#include "Aabb.h"
#include <vector>

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
                // NOTE: Run into issues when Volume >15^2 and density >=.9. Not sure why, but that's a hard limit.
                FixedPointInt calculatedMass = Material.Density * Shape.GetVolume();
                FixedPointInt maxMass = 15.0_fp * 15.0_fp * 0.9_fp;

                Mass.Mass = FixedPointInt::minimum(calculatedMass, maxMass);
                Mass.InverseMass(); // precalculate inv mass
            };

            ShapeData Shape;

            Aabb GetRoughAabb();
            std::vector<EVector> GetPoints(){
                std::vector<EVector> points = Shape.GetPoints();

                std::vector<EVector>::iterator it;

                for (it = points.begin(); it < points.end(); it++){
                    *it += Transform.Position;
                }


                return points; // note: doesn't actually apply transforms yet}
            };

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
