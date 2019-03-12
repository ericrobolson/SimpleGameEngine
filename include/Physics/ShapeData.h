#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include "Aabb.h"

namespace SGE_Physics{
class ShapeData
{
    public:
        ShapeData();
        virtual ~ShapeData();

        enum ShapeTypes{Circle, AABB};

        const ShapeTypes ShapeType = ShapeTypes::AABB;

        void SetAabb(Aabb aabb);

        Aabb GetAabb();

    protected:

    private:
        Aabb _aabb;
};

}


#endif // SHAPEDATA_H
