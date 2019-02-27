#include "catch.hpp"
#include "EVector.h"

#include "FixedPointInt.h"

using namespace SGE_Math;

SCENARIO("EVector:: dot()"){
    EVector ev1, ev2;
    FixedPointInt fp;

    ev1.X = 2.0_fp;
    ev1.Y = 4.0_fp;

    ev2.X = 1.0_fp;
    ev2.Y = 2.0_fp;

    fp = ev1.dot(ev2);

    REQUIRE(ev1.X == 2.0_fp);
    REQUIRE(ev1.Y == 4.0_fp);

    REQUIRE(ev2.X == 1.0_fp);
    REQUIRE(ev2.Y == 2.0_fp);

    // ev1 dot ev2 = (2.0 * 1.0 + 4.0 * 2.0)
    REQUIRE(fp == 10.00_fp);


    ev1.X = 0.5_fp;
    ev1.Y = 4.3_fp;

    ev2.X = -2.1_fp;
    ev2.Y = 33.33_fp;

    fp = ev1.dot(ev2);

    REQUIRE(ev1.X == 0.5_fp);
    REQUIRE(ev1.Y == 4.3_fp);

    REQUIRE(ev2.X == -2.1_fp);
    REQUIRE(ev2.Y == 33.33_fp);

    // ev1 dot ev2 = (0.5 * -2.1 + 4.3 * 33.33)
    REQUIRE(fp == 142.27_fp);
}


