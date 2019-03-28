#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include "Aabb.h"
#include "FixedPointInt.h"

namespace SGE_Physics{
class ShapeData
{
    public:
        ShapeData();
        virtual ~ShapeData();

        enum ShapeTypes{Circle, AABB};

        const ShapeTypes ShapeType = ShapeTypes::AABB;

        FixedPointInt GetVolume(){
            return (_aabb.HalfHeight * 2.0_fp) * (_aabb.HalfWidth * 2.0_fp);
        };

        void SetAabb(Aabb aabb);

        Aabb GetAabb();

    protected:

    private:
        Aabb _aabb;
};

}


#endif // SHAPEDATA_H
