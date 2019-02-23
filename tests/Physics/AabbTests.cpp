#include "catch.hpp"
#include "Aabb.h"
using namespace SGE_Physics;
#include "FixedPointInt.h"
using namespace SGE_Math;

SCENARIO("Aabb::MinCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2;
    aabb.HalfHeight = 5;
    aabb.Position.Coordinates.X = 2;
    aabb.Position.Coordinates.Y = 5;

    Coordinate minCoordinate = aabb.MinCoordinate();

    FixedPointInt expectedX, expectedY;
    expectedX = 0;
    expectedY = 0;

    REQUIRE(minCoordinate.X == expectedX);
    REQUIRE(minCoordinate.Y == expectedY);
}


SCENARIO("Aabb::MaxCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2;
    aabb.HalfHeight = 6;
    aabb.Position.Coordinates.X = 3;
    aabb.Position.Coordinates.Y = 5;

    Coordinate minCoordinate = aabb.MaxCoordinate();

    FixedPointInt expectedX, expectedY;
    expectedX = (2 + 3);
    expectedY = (6 + 5);

    REQUIRE(minCoordinate.X == expectedX);
    REQUIRE(minCoordinate.Y == expectedY);
}
