#include "catch.hpp"
#include "Aabb.h"
using namespace SGE_Physics;

SCENARIO("Aabb::MinCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2;
    aabb.HalfHeight = 5;
    aabb.Position.Coordinates.X = 2;
    aabb.Position.Coordinates.Y = 5;

    Coordinate minCoordinate = aabb.MinCoordinate();

    REQUIRE(minCoordinate.X == (2 - 2));
    REQUIRE(minCoordinate.Y == (5 - 5));
}


SCENARIO("Aabb::MaxCoordinate(): Returns expected calculated coordinate"){
    Aabb aabb;

    aabb.HalfWidth = 2;
    aabb.HalfHeight = 6;
    aabb.Position.Coordinates.X = 3;
    aabb.Position.Coordinates.Y = 5;

    Coordinate minCoordinate = aabb.MaxCoordinate();

    REQUIRE(minCoordinate.X == (2 + 3));
    REQUIRE(minCoordinate.Y == (6 + 5));
}
