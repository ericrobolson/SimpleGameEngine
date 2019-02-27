#include "catch.hpp"
#include "EVector.h"

using namespace SGE_Math;

SCENARIO("EVector:: != operator"){
    EVector ev1, ev2;

    // ev1 != ev2
    ev1.X = 2.0_fp;
    ev1.Y = 4.0_fp;

    ev2.X = 1.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 != ev2) == true);

    // ev1 = ev2
    ev1.X = 4.0_fp;
    ev1.Y = 2.0_fp;

    ev2.X = 4.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 != ev2) == false);

    // X is same, Y is different
    ev1.X = -4.0_fp;
    ev1.Y = 2.2_fp;

    ev2.X = -4.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 != ev2) == true);

    // X is different, Y is same
    ev1.X = -4.0_fp;
    ev1.Y = 2.2_fp;

    ev2.X = 4.0_fp;
    ev2.Y = 2.2_fp;

    REQUIRE((ev1 != ev2) == true);
}


SCENARIO("EVector:: == operator"){
    EVector ev1, ev2;

    // ev1 != ev2
    ev1.X = 2.0_fp;
    ev1.Y = 4.0_fp;

    ev2.X = 1.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 == ev2) == false);

    // ev1 = ev2
    ev1.X = 4.0_fp;
    ev1.Y = 2.0_fp;

    ev2.X = 4.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 == ev2) == true);

    // X is same, Y is different
    ev1.X = -4.0_fp;
    ev1.Y = 2.2_fp;

    ev2.X = -4.0_fp;
    ev2.Y = 2.0_fp;

    REQUIRE((ev1 == ev2) == false);

    // X is different, Y is same
    ev1.X = -4.0_fp;
    ev1.Y = 2.2_fp;

    ev2.X = 4.0_fp;
    ev2.Y = 2.2_fp;

    REQUIRE((ev1 == ev2) == false);
}

