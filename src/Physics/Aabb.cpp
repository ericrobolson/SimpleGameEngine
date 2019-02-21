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

    c.X = Position.Coordinates.X - HalfWidth;
    c.Y = Position.Coordinates.Y - HalfHeight;

    return c;
}

Coordinate Aabb::MaxCoordinate(){
    Coordinate c;

    c.X = Position.Coordinates.X + HalfWidth;
    c.Y = Position.Coordinates.Y + HalfHeight;

    return c;
}
