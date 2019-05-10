
#include "catch.hpp"
#include "CollisionDectector.h"
#include "Aabb.h"
#include "Physics/Circle.h"
#include "CollisionData.h"
#include "Body.h"
#include <memory>
using namespace SGE_Physics;


void SetupBody(Body& body, FixedPointInt aabbHh, FixedPointInt aabbHw,FixedPointInt x, FixedPointInt y){

    Aabb a;
    a.HalfHeight = aabbHh;
    a.HalfWidth = aabbHw;

    EVector entity1Position;
    entity1Position.X = x;
    entity1Position.Y = y;

    body.Initialize(MaterialData::MaterialType::Metal, entity1Position, a);

}



/*
TEST_CASE("CollisionDectector::AabbVsAabb() No intersection bodies returns false."){

//    CollisionData cd;

    cd.Entity1 = std::make_shared<Body>();
    cd.Entity2 = std::make_shared<Body>();

    SetupBody(*cd.Entity1, 10.0_fp, 10.0_fp, 1.0_fp, 10.0_fp);
    SetupBody(*cd.Entity2, 50.0_fp, 300.0_fp, 15.0_fp, 600.0_fp);

    REQUIRE(CollisionDectector::AabbVsAabb(cd) == false);

    // tests using actual data
    SetupBody(*cd.Entity1, 10.0_fp, 10.0_fp, 450.0_fp, 543.0_fp);
    SetupBody(*cd.Entity2, 50.0_fp, 300.0_fp, 15.0_fp, 600.0_fp);

    REQUIRE(CollisionDectector::AabbVsAabb(cd) == false);
    //

    SetupBody(*cd.Entity1, 10.0_fp, 10.0_fp, 450.0_fp, 612.0_fp);
    SetupBody(*cd.Entity2, 50.0_fp, 300.0_fp, 15.0_fp, 600.0_fp);

    REQUIRE(CollisionDectector::AabbVsAabb(cd) == true);


    // todo: write up tests
    // usse actual data to check for collisions

    /*
// note: go through each of these and check to make sure that they return a position and/or a valid collision
// uses player object, and the big object
    e1 pos: (450, 543)
e2 pos: (15, 600)
n.X: -435
n.Y: 57
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 545)
e2 pos: (15, 600)
n.X: -435
n.Y: 55
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 547)
e2 pos: (15, 600)
n.X: -435
n.Y: 53
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 548)
e2 pos: (15, 600)
n.X: -435
n.Y: 52
no collision

e1 pos: (450, 606)
e2 pos: (15, 600)
n.X: -435
n.Y: -6
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 609)
e2 pos: (15, 600)
n.X: -435
n.Y: -9
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 612)
e2 pos: (15, 600)
n.X: -435
n.Y: -12
no collision
xxxxxxxxxxxxxxxxxxxxx
e1 pos: (450, 614)
e2 pos: (15, 600)
n.X: -435
n.Y: -14
no collision
    */






/*

SCENARIO("CollisionDectector::AabbVsAabb: No collision returns false"){
    Aabb a;
    a.Position.X = 0.0_fp;
    a.Position.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.X = 10.0_fp;
    b.Position.Y = 10.0_fp;
    b.HalfHeight = 2.0_fp;
    b.HalfWidth = 2.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == false);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Xaxis returns true"){
    Aabb a;
    a.Position.X = 0.0_fp;
    a.Position.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.X = 10.0_fp;
    b.Position.Y = 0.0_fp;
    b.HalfHeight = 2.0_fp;
    b.HalfWidth = 20.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Yaxis returns true"){
    Aabb a;
    a.Position.X = 0.0_fp;
    a.Position.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.X = 0.0_fp;
    b.Position.Y = 10.0_fp;
    b.HalfHeight = 20.0_fp;
    b.HalfWidth = 20.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}










SCENARIO("CollisionDectector::CircleVsCircle: No collision returns false"){
    Circle a;
    a.Position.X = 0.0_fp;
    a.Position.Y = 0.0_fp;
    a.Radius = 2.0_fp;

    Circle b;
    b.Position.X = 4.0_fp;
    b.Position.Y = 4.0_fp;
    b.Radius = 2.0_fp;


    CollisionDectector cd;

    REQUIRE(cd.CircleVsCircle(a, b) == false);
}

SCENARIO("CollisionDectector::CircleVsCircle: Collision returns true"){
    Circle a;
    a.Position.X = 0.0_fp;
    a.Position.Y = 0.0_fp;
    a.Radius = 4.0_fp;

    Circle b;
    b.Position.X = 4.0_fp;
    b.Position.Y = 4.0_fp;
    b.Radius = 4.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.CircleVsCircle(a, b) == true);
}
*/
