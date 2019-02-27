#include "catch.hpp"
#include "EVector.h"

using namespace SGE_Math;

SCENARIO("EVector:: -= minus operator"){
    EVector ev1, ev2;

    ev1.X = 0.23_fp;
    ev1.Y = -23.21_fp;

    ev2.X = 4.23_fp;
    ev2.Y = 43.21_fp;

    ev2 -= ev1;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);

    REQUIRE(ev2.X == 4.0_fp);
    REQUIRE(ev2.Y == 66.42_fp);
}

SCENARIO("EVector:: += minus operator"){
    EVector ev1, ev2;

    ev1.X = 0.23_fp;
    ev1.Y = -23.21_fp;

    ev2.X = 4.23_fp;
    ev2.Y = 43.21_fp;

    ev2 += ev1;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);

    REQUIRE(ev2.X == 4.46_fp);
    REQUIRE(ev2.Y == 20.00_fp);
}

