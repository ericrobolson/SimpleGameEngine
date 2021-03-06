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

    if (aMax < bMax && aMax > bMin || aMin > bMin && aMin < bMax){
        return true;
    }


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

static std::vector<EVector> GetNormals(std::vector<EVector> points){
    std::vector<EVector> normals;

    // loop over each edge to calculate the normal
    for (int i = 0; i < points.size(); i++){

        // Construct the edge
        EVector ev1 = points[i];

        int ev2Index = (i + 1) == points.size() ? 0 : i + 1;

        EVector ev2 = points[ev2Index];


        EVector edgeVector = ev1 - ev2;

        EVector normal;
        normal.X = -edgeVector.Y;
        normal.Y = edgeVector.X;

        normal.Normalize();

        normals.push_back(normal);
    }


    return normals;
}


static bool Overlap(FixedPointInt& minOverlap, EVector& minNormal, const std::vector<EVector>& axi, const std::vector<EVector>& entity1Points, const std::vector<EVector>& entity2Points){

    for (int i = 0; i < axi.size(); i++){
        EVector axis = axi[i];

        EVector::Projection projection1 = axis.project(entity1Points);
        EVector::Projection projection2 = axis.project(entity2Points);

        // check if axis is separating
        FixedPointInt n = projection1.Max - projection2.Min;

        FixedPointInt extent1 = projection1.Max - projection1.Min;
        FixedPointInt extent2 = projection2.Max - projection2.Min;

        FixedPointInt overlap = (extent1 + extent2) - n.abs();

        // if negative, no overlap
        if (overlap < 0.0_fp){
            return false;
        }

        if (overlap < minOverlap){
            minNormal = -axis;
            minOverlap = overlap;
        }
    }

    return true;
}

static bool PolygonVsPolygon(CollisionData& cd){
    std::vector<EVector> entity1Points = cd.Entity1.GetPoints();
    std::vector<EVector> entity2Points = cd.Entity2.GetPoints();


    // Get the axis' to perform SAT on by getting the normals
    std::vector<EVector> entity1Axises = GetNormals(entity1Points);
    std::vector<EVector> entity2Axises = GetNormals(entity2Points);

    EVector minNormal;

    // Set the minOverlap to a really big value
    FixedPointInt minOverlap;
    minOverlap.Value = minOverlap.MAXVALUE;

    // Loop over the Axises for entity1
    if (Overlap(minOverlap, minNormal, entity1Axises, entity1Points, entity2Points) == false){
        return false;
    }

    // Loop over the Axises for entity2
    if (Overlap(minOverlap, minNormal, entity2Axises, entity1Points, entity2Points) == false){
        return false;
    }

    cd.Normal = minNormal;

    cd.Penetration = minOverlap;
    return true;
}


bool CollisionDectector::CheckCollision(CollisionData& cd){



    // broad phase check before diving into specific checks
    if (AabbVsAabb(cd.Entity1.GetRoughAabb(), cd.Entity2.GetRoughAabb()) == false){
        return false;
    }

        return (PolygonVsPolygon(cd));


    return AabbVsAabb(cd);


    ShapeData::ShapeTypes entity1ShapeType = cd.Entity1.Shape.ShapeType;
    ShapeData::ShapeTypes entity2ShapeType = cd.Entity2.Shape.ShapeType;

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

/*
void Debug(CollisionData& cd, EVector n, FixedPointInt xOverlap, FixedPointInt yOverlap, FixedPointInt aExtentX, FixedPointInt aExtentY, FixedPointInt bExtentX, FixedPointInt bExtentY){
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

    SGE::Debugger::Instance().WriteMessage("aExtent: ("
                                           + std::to_string((int) aExtentX)
                                           + ", "
                                           + std::to_string((int) aExtentY)
                                           + ")"
                                           );

     SGE::Debugger::Instance().WriteMessage("bExtent: ("
                                           + std::to_string((int) bExtentX)
                                           + ", "
                                           + std::to_string((int) bExtentY)
                                           + ")"
                                           );
    SGE::Debugger::Instance().WriteMessage("xOverlap: " + std::to_string((int) xOverlap));
    SGE::Debugger::Instance().WriteMessage("yOverlap: " + std::to_string((int) yOverlap));

}
*/

bool CollisionDectector::AabbVsAabb(EVector& positionA, EVector& positionB, Aabb abox, Aabb bbox, EVector& normal, FixedPointInt& penetration){
    EVector n = positionB - positionA;

    // issue: when one is inside the other?
    EVector aMin = abox.MinCoordinate();
    EVector aMax = abox.MaxCoordinate();

    EVector bMin = bbox.MinCoordinate();
    EVector bMax = bbox.MaxCoordinate();

    bool collided = aMax < bMax && aMax > bMin || aMin > bMin && aMin < bMax;

    if (!collided){
        return false;
    }

    // Calculate half extents along x axis for each object

    FixedPointInt xOverlap = abox.HalfWidth + bbox.HalfWidth - (n.X.abs());

    FixedPointInt yOverlap = abox.HalfHeight + bbox.HalfHeight - (n.Y.abs());

    EVector ev;
    // note: issue with normal calculations when one object is project inside another

    if (xOverlap > yOverlap){

        if (n.X.Value < 0){
            ev.X = -1.0_fp;
        }else{
            ev.X = 1.0_fp;
        }

        penetration = xOverlap;
    }else{
        if (n.Y.Value < 0){
            ev.Y = -1.0_fp;
        }else{
            ev.Y = 1.0_fp;
        }

        penetration = yOverlap;
    }


    normal = ev;
    return true;

}

bool CollisionDectector::AabbVsAabb(CollisionData& cd){
    // does the ordering matter? Something seems funky with all collision resolution except when small object collides with bottom of big object

    // todo: rename; but this is the vector from Entity1 to entity2
    EVector n = cd.Entity2.Transform.Position - cd.Entity1.Transform.Position;


    Aabb abox, bbox;

    abox = cd.Entity1.GetRoughAabb();
    bbox = cd.Entity2.GetRoughAabb();





    /*
    // issue: when one is inside the other?

    // Entity1 vs Entity2
    if (AabbVsAabb(cd.Entity1.Transform.Position, cd.Entity2.Transform.Position, abox, bbox, cd.Normal, cd.Penetration)){
        return true;
    }


    // Entity2 vs Entity1
    return AabbVsAabb(cd.Entity1.Transform.Position, cd.Entity2.Transform.Position, abox, bbox, cd.Normal, cd.Penetration);


    if (AabbVsAabb(abox, bbox) == false){
        return false;
    }





    // Calculate half extents along x axis for each object

    FixedPointInt xOverlap = abox.HalfWidth + bbox.HalfWidth - (n.X.abs());

    FixedPointInt yOverlap = abox.HalfHeight + bbox.HalfHeight - (n.Y.abs());

    EVector ev;
    // note: issue with normal calculations when one object is project inside another

    if (xOverlap > yOverlap){

        if (n.X.Value < 0){
            ev.X = -1.0_fp;
        }else{
            ev.X = 1.0_fp;
        }

        cd.Penetration = xOverlap;
    }else{
        if (n.Y.Value < 0){
            ev.Y = -1.0_fp;
        }else{
            ev.Y = 1.0_fp;
        }

        cd.Penetration = yOverlap;
    }


    cd.Normal = ev;
    return true;
    */
}

bool CollisionDectector::AabbVsCircle(CollisionData& cd){
    // todo
    return false;
}

