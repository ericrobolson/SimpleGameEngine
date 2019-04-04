#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include "Aabb.h"
#include "FixedPointInt.h"
#include "EVector.h"
#include <vector>


namespace SGE_Physics{
class ShapeData
{
    public:
        // Note: All shape data must be a convex shape
        ShapeData();
        virtual ~ShapeData();

        enum ShapeTypes{Circle, AABB};

        const ShapeTypes ShapeType = ShapeTypes::AABB;

        FixedPointInt GetVolume(){
            return (_aabb.HalfHeight * 2.0_fp) * (_aabb.HalfWidth * 2.0_fp);
        };

        std::vector<EVector> GetPoints() {
            std::vector<EVector> points;

            EVector ev;
            points.push_back(_aabb.MinCoordinate());
            ev = _aabb.MinCoordinate();
            ev.X = _aabb.MaxCoordinate().X;

            points.push_back(ev);

            points.push_back(_aabb.MaxCoordinate());

            ev.Y = _aabb.MaxCoordinate().Y;
            ev.X = _aabb.MinCoordinate().X;

            points.push_back(ev);

            return points;


        };// Get the points for the shapedata, going in a clockwise motion.

        void SetAabb(Aabb aabb);

        Aabb GetAabb();

    protected:

    private:
        Aabb _aabb;
};

}


#endif // SHAPEDATA_H
