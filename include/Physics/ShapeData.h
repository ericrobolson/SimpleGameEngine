#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include "Aabb.h"

namespace SGE_Physics{
class ShapeData
{
    public:
        ShapeData();
        virtual ~ShapeData();

        Aabb GetAabb();

    protected:

    private:
};

}


#endif // SHAPEDATA_H
