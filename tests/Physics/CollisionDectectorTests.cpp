
#include "catch.hpp"
#include "CollisionDectector.h"
#include "Aabb.h"
using namespace SGE_Physics;


SCENARIO("CollisionDectector::AabbVsAabb: No collision returns false"){
    Aabb a;
    a.Position.Coordinates.X = 0;
    a.Position.Coordinates.Y = 0;
    a.HalfHeight = 2;
    a.HalfWidth = 2;

    Aabb b;
    b.Position.Coordinates.X = 10;
    b.Position.Coordinates.Y = 10;
    b.HalfHeight = 2;
    b.HalfWidth = 2;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == false);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Xaxis returns true"){
    Aabb a;
    a.Position.Coordinates.X = 0;
    a.Position.Coordinates.Y = 0;
    a.HalfHeight = 2;
    a.HalfWidth = 2;

    Aabb b;
    b.Position.Coordinates.X = 10;
    b.Position.Coordinates.Y = 0;
    b.HalfHeight = 2;
    b.HalfWidth = 20;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Yaxis returns true"){
    Aabb a;
    a.Position.Coordinates.X = 0;
    a.Position.Coordinates.Y = 0;
    a.HalfHeight = 2;
    a.HalfWidth = 2;

    Aabb b;
    b.Position.Coordinates.X = 0;
    b.Position.Coordinates.Y = 10;
    b.HalfHeight = 20;
    b.HalfWidth = 20;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
}
