#include "CollisionDectector.h"
#include <cmath>

#include "FixedPointInt.h"
#include "EVector.h"
#include "ShapeData.h"
#include "Debugger.h"
#include "MaterialData.h"
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

bool CollisionDectector::CheckCollision(CollisionData& cd){
    return AabbVsAabb(cd);



    ShapeData::ShapeTypes entity1ShapeType = cd.Entity1->Shape.ShapeType;
    ShapeData::ShapeTypes entity2ShapeType = cd.Entity2->Shape.ShapeType;

    // Check the collision depending on the entity shapes
    if (entity1ShapeType == entity2ShapeType){
        if (entity1ShapeType == ShapeData::Circle){
            return CircleVsCircle(cd);
        }
        else if (entity1ShapeType == ShapeData::AABB){
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

bool CollisionDectector::CircleVsCircle(CollisionData& cd){
    // todo
    return false;
}

// Order the vectors, so A contains the smallest points and B contains the max points
void OrderVectors(EVector& a, EVector& b){
    FixedPointInt i;

    if (a.X > b.X){
        i = b.X;
        b.X = a.X;
        a.X = i;
    }

    if (a.Y > b.Y){
        i = b.Y;
        b.Y = a.Y;
        a.Y = i;
    }
}


bool CollisionDectector::AabbVsAabb(CollisionData& cd){
    // does the ordering matter? Something seems funky with all collision resolution except when small object collides with bottom of big object


    // todo: rename; but this is the vector from Entity1 to entity2
    EVector n = cd.Entity2->Transform.Position - cd.Entity1->Transform.Position;

    SGE::Debugger::Instance().WriteMessage("xxxxxxxxxxxxxxxxxxxxx");
    SGE::Debugger::Instance().WriteMessage(
       "e1 pos: ("
       + std::to_string(((int)cd.Entity1->Transform.Position.X))
                                           + ", "
       + std::to_string(((int)cd.Entity1->Transform.Position.Y))
                + ")");

    SGE::Debugger::Instance().WriteMessage(
       "e2 pos: ("
       + std::to_string(((int)cd.Entity2->Transform.Position.X))
                                           + ", "
       + std::to_string(((int)cd.Entity2->Transform.Position.Y))
                + ")");

    SGE::Debugger::Instance().WriteMessage("n.X: " + std::to_string((int) n.X));
    SGE::Debugger::Instance().WriteMessage("n.Y: " + std::to_string((int) n.Y));


    Aabb abox = cd.Entity1->GetRoughAabb();
    Aabb bbox = cd.Entity2->GetRoughAabb();

    EVector aMin = abox.MinCoordinate();
    EVector aMax = abox.MaxCoordinate();

    EVector bMin = bbox.MinCoordinate();
    EVector bMax = bbox.MaxCoordinate();

    // Calculate half extents along x axis for each object
    FixedPointInt aExtentX = (aMax.X - aMin.X).abs() / 2.0_fp;
    FixedPointInt bExtentX = (bMax.X - bMin.X).abs() / 2.0_fp;

    FixedPointInt xOverlap = aExtentX + bExtentX - (n.X.abs());

    FixedPointInt aExtentY = (aMax.Y - aMin.Y).abs() / 2.0_fp;
    FixedPointInt bExtentY = (bMax.Y - bMin.Y).abs() / 2.0_fp;

    FixedPointInt yOverlap = aExtentY + bExtentY - (n.Y.abs());

    if (yOverlap > 0.0_fp || xOverlap > 0.0_fp){
            SGE::Debugger::Instance().WriteMessage("no collision");
        return false;
    }

    SGE::Debugger::Instance().WriteMessage("XX collision");

    EVector ev;
    if (xOverlap >= yOverlap){

        if (n.X.Value <= 0){
            ev.X = 1.0_fp;
        }else{
            ev.X = -1.0_fp;
        }

        cd.Penetration = xOverlap;
    }else{
        if (n.Y.Value <= 0){
            ev.Y = 1.0_fp;
        }else{
            ev.Y = -1.0_fp;
        }

        cd.Penetration = yOverlap;
    }

    cd.Normal = ev;
    return true;
}

bool CollisionDectector::AabbVsCircle(CollisionData& cd){
    // todo
    return false;
}

