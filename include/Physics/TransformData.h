#ifndef TRANSFORMDATA_H
#define TRANSFORMDATA_H
#include "Coordinate.h"
namespace SGE_Physics{
class TransformData
{
    public:
        TransformData();
        virtual ~TransformData();

        Coordinate Coordinates;
        float Radians;

    protected:

    private:
};

}

#endif // TRANSFORMDATA_H
