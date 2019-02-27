#include "catch.hpp"
#include "EVector.h"

using namespace SGE_Math;

SCENARIO("EVector:: ="){
    EVector ev1;
    EVector ev2;

    ev2.X = 0.23_fp;
    ev2.Y = -23.21_fp;

    ev1 = ev2;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);
    REQUIRE(ev2.X == 0.23_fp);
    REQUIRE(ev2.Y == -23.21_fp);
}

