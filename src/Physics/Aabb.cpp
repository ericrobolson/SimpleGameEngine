#include "Physics/Aabb.h"
#include "Coordinate.h"
using namespace SGE_Physics;

Aabb::Aabb()
{
    //ctor
}

Aabb::~Aabb()
{
    //dtor
}

Coordinate Aabb::MinCoordinate(){
    Coordinate c;

    c.X = Position.X - HalfWidth;
    c.Y = Position.Y - HalfHeight;

    return c;
}

Coordinate Aabb::MaxCoordinate(){
    Coordinate c;

    c.X = Position.X + HalfWidth;
    c.Y = Position.Y + HalfHeight;

    return c;
}
