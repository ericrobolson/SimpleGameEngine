#include "catch.hpp"
#include "EVector.h"

using namespace SGE_Math;

SCENARIO("EVector:: Constructor()"){
    EVector ev1;

    REQUIRE(ev1.X == 0.0_fp);
    REQUIRE(ev1.Y == 0.0_fp);
}

SCENARIO("EVector:: Constructor(Evector&)"){
    EVector ev1;
    ev1.X = 1.23_fp;
    ev1.Y = 288.32_fp;


    EVector ev2(ev1);

    REQUIRE(ev1.X == 1.23_fp);
    REQUIRE(ev1.Y == 288.32_fp);

    REQUIRE(ev2.X == 1.23_fp);
    REQUIRE(ev2.Y == 288.32_fp);
}
