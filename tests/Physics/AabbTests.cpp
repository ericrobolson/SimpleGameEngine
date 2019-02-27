#include "catch.hpp"
#include "Aabb.h"
using namespace SGE_Physics;
#include "FixedPointInt.h"
using namespace SGE_Math;

SCENARIO("Aabb::MinCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2.0_fp;
    aabb.HalfHeight = 5.0_fp;
    aabb.Position.X = 2.0_fp;
    aabb.Position.Y = 5.0_fp;

    Coordinate minCoordinate = aabb.MinCoordinate();

    FixedPointInt expectedX, expectedY;
    expectedX = 0.0_fp;
    expectedY = 0.0_fp;

    REQUIRE(minCoordinate.X == expectedX);
    REQUIRE(minCoordinate.Y == expectedY);
}


SCENARIO("Aabb::MaxCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2.0_fp;
    aabb.HalfHeight = 6.0_fp;
    aabb.Position.X = 3.0_fp;
    aabb.Position.Y = 5.0_fp;

    Coordinate minCoordinate = aabb.MaxCoordinate();

    FixedPointInt expectedX, expectedY;
    expectedX = 5.0_fp;
    expectedY = 11.0_fp;

    REQUIRE(minCoordinate.X == expectedX);
    REQUIRE(minCoordinate.Y == expectedY);
}
