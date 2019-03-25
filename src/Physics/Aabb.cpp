#include "Physics/Aabb.h"
#include "EVector.h"
using namespace SGE_Math;
using namespace SGE_Physics;

Aabb::Aabb()
{
    //ctor
}

Aabb::~Aabb()
{
    //dtor
}

EVector Aabb::MinCoordinate(){
    EVector v;

    v.X = Position.X;
    v.Y = Position.Y;

    return v;
}

EVector Aabb::MaxCoordinate(){
      EVector v;

    v.X = Position.X + (HalfWidth * 2.0_fp);
    v.Y = Position.Y + (HalfHeight * 2.0_fp);

    return v;
}
