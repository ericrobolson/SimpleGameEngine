#include "CollisionDectector.h"
#include <cmath>

using namespace SGE_Physics;
CollisionDectector::CollisionDectector()
{
    //ctor
}

CollisionDectector::~CollisionDectector()
{
    //dtor
}


bool CollisionDectector::AabbVsAabb( Aabb a, Aabb b )
{
    Coordinate aMin = a.MinCoordinate();
    Coordinate aMax = a.MaxCoordinate();

    Coordinate bMin = b.MinCoordinate();
    Coordinate bMax = b.MaxCoordinate();

  // Exit with no intersection if found separated along an axis
  if(aMax.X < bMin.X || aMin.X > bMax.X){
    return false;
  }

  if(aMax.Y < bMin.Y || aMin.Y > bMax.Y){
    return false;
  }

  // No separating axis found, therefor there is at least one overlapping axis
  return true;
}


bool CollisionDectector::CircleVsCircle(Circle a, Circle b){
    // Uses the algorithm to determine intersecting circles:
    // ABS(R0 - R1) <= SQRT((x0 - x1)^2 + (y0 - y1)^2) <= (R0 + R1)
    // Raised all sides by a power of 2 removes the SQRT operator

    int lowerBound = pow((a.Radius - b.Radius),2);
    int upperBound = pow((a.Radius + b.Radius),2);

    int distance = pow((a.Position.Coordinates.X - b.Position.Coordinates.X), 2) + pow((a.Position.Coordinates.Y - b.Position.Coordinates.Y), 2);

    return lowerBound <= distance && distance <= upperBound;
}
