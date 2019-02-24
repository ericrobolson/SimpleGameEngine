#include "CollisionDectector.h"
#include <cmath>

#include "FixedPointInt.h"
using namespace SGE_Math;

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

    FixedPointInt lowerBound = (a.Radius - b.Radius)*(a.Radius - b.Radius);
    FixedPointInt upperBound = (a.Radius + b.Radius)*(a.Radius + b.Radius);

    FixedPointInt distance =
    ((a.Position.Coordinates.X - b.Position.Coordinates.X)*(a.Position.Coordinates.X - b.Position.Coordinates.X))
    + ((a.Position.Coordinates.Y - b.Position.Coordinates.Y)*(a.Position.Coordinates.Y - b.Position.Coordinates.Y));

    return lowerBound <= distance && distance <= upperBound;
}
