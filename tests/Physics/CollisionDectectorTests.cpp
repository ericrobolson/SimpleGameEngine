
#include "catch.hpp"
#include "CollisionDectector.h"
#include "Aabb.h"
#include "Physics/Circle.h"
using namespace SGE_Physics;


SCENARIO("CollisionDectector::AabbVsAabb: No collision returns false"){
    Aabb a;
    a.Position.Coordinates.X = 0.0_fp;
    a.Position.Coordinates.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.Coordinates.X = 10.0_fp;
    b.Position.Coordinates.Y = 10.0_fp;
    b.HalfHeight = 2.0_fp;
    b.HalfWidth = 2.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == false);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Xaxis returns true"){
    Aabb a;
    a.Position.Coordinates.X = 0.0_fp;
    a.Position.Coordinates.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.Coordinates.X = 10.0_fp;
    b.Position.Coordinates.Y = 0.0_fp;
    b.HalfHeight = 2.0_fp;
    b.HalfWidth = 20.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Yaxis returns true"){
    Aabb a;
    a.Position.Coordinates.X = 0.0_fp;
    a.Position.Coordinates.Y = 0.0_fp;
    a.HalfHeight = 2.0_fp;
    a.HalfWidth = 2.0_fp;

    Aabb b;
    b.Position.Coordinates.X = 0.0_fp;
    b.Position.Coordinates.Y = 10.0_fp;
    b.HalfHeight = 20.0_fp;
    b.HalfWidth = 20.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}

SCENARIO("CollisionDectector::CircleVsCircle: No collision returns false"){
    Circle a;
    a.Position.Coordinates.X = 0.0_fp;
    a.Position.Coordinates.Y = 0.0_fp;
    a.Radius = 2.0_fp;

    Circle b;
    b.Position.Coordinates.X = 4.0_fp;
    b.Position.Coordinates.Y = 4.0_fp;
    b.Radius = 2.0_fp;


    CollisionDectector cd;

    REQUIRE(cd.CircleVsCircle(a, b) == false);
}

SCENARIO("CollisionDectector::CircleVsCircle: Collision returns true"){
    Circle a;
    a.Position.Coordinates.X = 0.0_fp;
    a.Position.Coordinates.Y = 0.0_fp;
    a.Radius = 4.0_fp;

    Circle b;
    b.Position.Coordinates.X = 4.0_fp;
    b.Position.Coordinates.Y = 4.0_fp;
    b.Radius = 4.0_fp;

    CollisionDectector cd;

    REQUIRE(cd.CircleVsCircle(a, b) == true);
}
