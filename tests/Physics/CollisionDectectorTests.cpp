
#include "catch.hpp"
#include "CollisionDectector.h"
#include "Aabb.h"
using namespace SGE_Physics;


SCENARIO("CollisionDectector::AabbVsAabb: No collision returns false"){
    /*

    Aabb a;
    a.Min.X = 0;
    a.Min.Y = 0;
    a.Max.X = 2;
    a.Max.Y = 2;


    Aabb b;
    b.Min.X = 4;
    b.Min.Y = 4;
    b.Max.X = 6;
    b.Max.Y = 6;


    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == false);
    */
    REQUIRE(true == false);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Xaxis returns true"){
    /*
    Aabb a;
    a.Min.X = 0;
    a.Min.Y = 0;
    a.Max.X = 2;
    a.Max.Y = 2;


    Aabb b;
    b.Min.X = -1;
    b.Min.Y = 0;
    b.Max.X = 6;
    b.Max.Y = 2;


    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
    */
    REQUIRE(true == false);
}

SCENARIO("CollisionDectector::AabbVsAabb: Overlap on Yaxis returns true"){
    /*
    Aabb a;
    a.Min.X = 0;
    a.Min.Y = 0;
    a.Max.X = 2;
    a.Max.Y = 6;

    Aabb b;
    b.Min.X = 0;
    b.Min.Y = 0;
    b.Max.X = 2;
    b.Max.Y = 2;

    CollisionDectector cd;

    REQUIRE(cd.AabbVsAabb(a, b) == true);
    */
    REQUIRE(true == false);
}
