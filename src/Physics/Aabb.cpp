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

    v.X = Position.X - HalfWidth;
    v.Y = Position.Y - HalfHeight;

    return v;
}

EVector Aabb::MaxCoordinate(){
      EVector v;

    v.X = Position.X + HalfWidth;
    v.Y = Position.Y + HalfHeight;

    return v;
}
