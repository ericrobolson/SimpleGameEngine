#include "CollisionDectector.h"
#include <cmath>

#include "FixedPointInt.h"
#include "EVector.h"
#include "ShapeData.h"
#include "Debugger.h"
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
    EVector aMin = a.MinCoordinate();
    EVector aMax = a.MaxCoordinate();

    EVector bMin = b.MinCoordinate();
    EVector bMax = b.MaxCoordinate();

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
    ((a.Position.X - b.Position.X)*(a.Position.X - b.Position.X))
    + ((a.Position.Y - b.Position.Y)*(a.Position.Y - b.Position.Y));

    return lowerBound <= distance && distance <= upperBound;
}

bool CollisionDectector::CheckCollision(std::shared_ptr<CollisionData> cd){

    ShapeData::ShapeTypes entity1ShapeType = cd->Entity1->Shape.ShapeType;
    ShapeData::ShapeTypes entity2ShapeType = cd->Entity2->Shape.ShapeType;

    // Check the collision depending on the entity shapes
    if (entity1ShapeType == entity2ShapeType){
        if (entity1ShapeType == ShapeData::Circle){
            return CircleVsCircle(cd);
        }
        else if (entity1ShapeType == ShapeData::AABB){
            return AabbVsAabb(cd);
        }
    }
    else{
        if ((entity1ShapeType == ShapeData::AABB && entity2ShapeType == ShapeData::Circle)
            || (entity1ShapeType == ShapeData::Circle && entity2ShapeType == ShapeData::AABB)){
            return AabbVsCircle(cd);
        }
    }

    return false;
}

bool CollisionDectector::CircleVsCircle(std::shared_ptr<CollisionData> cd){
    // todo
    return false;
}

bool CollisionDectector::AabbVsAabb(std::shared_ptr<CollisionData> cd){

    // todo: rename; but this is the vector from Entity1 to entity2
    EVector n = cd->Entity1->Transform.Position - cd->Entity2->Transform.Position;

    Aabb abox = cd->Entity1->Shape.GetAabb();
    Aabb bbox = cd->Entity2->Shape.GetAabb();

    // Calculate half extents along x axis for each object
    FixedPointInt aExtentX = abox.HalfWidth;
    FixedPointInt bExtentX = bbox.HalfWidth;

    FixedPointInt xOverlap = aExtentX + bExtentX - n.X.abs();

    // SAT test on x axis
    if (xOverlap.Value > 0){
        // Calculate half extents along y axis for each object
        FixedPointInt aExtentY = abox.HalfHeight;
        FixedPointInt bExtentY = bbox.HalfHeight;

        FixedPointInt yOverlap = aExtentY + bExtentY - n.Y.abs();

        if (yOverlap.Value > 0){
            // Find out which axis is axis of least penetration
            if (xOverlap > yOverlap){
                // Point towards A knowing that n points from A to B; not sure if accurate but that's the general idea
                if (n.X.Value < 0){
                    EVector ev;
                    ev.X = -1.0_fp;
                    ev.Y = 0.0_fp;
                    cd->Normal = ev;
                }
                else{
                    EVector ev;
                    ev.X = 0.0_fp;
                    ev.Y = 0.0_fp;
                    cd->Normal = ev;
                }

                cd->Penetration = xOverlap;

                SGE::Debugger::Instance().WriteMessage("Collision.");
                return true;
            }
        }
        else{
            // Point towards B knowing that n points from A to B; not sure if accurate but that's the general idea
             if (n.Y.Value < 0){
                    EVector ev;
                    ev.X = 0.0_fp;
                    ev.Y = -1.0_fp;
                    cd->Normal = ev;
            }
            else{
                EVector ev;
                ev.X = 0.0_fp;
                ev.Y = 1.0_fp;
                cd->Normal = ev;
            }

            cd->Penetration = yOverlap;

            SGE::Debugger::Instance().WriteMessage("Collision.");
            return true;
        }
    }

    return false;
}

bool CollisionDectector::AabbVsCircle(std::shared_ptr<CollisionData> cd){
    // todo
    return false;
}

