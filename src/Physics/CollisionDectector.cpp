#include "CollisionDectector.h"

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
