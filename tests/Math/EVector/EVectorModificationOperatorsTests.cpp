#include "catch.hpp"
#include "EVector.h"

using namespace SGE_Math;

SCENARIO("EVector:: - negative operator"){
    EVector ev1;
    EVector ev2;

    ev1.X = 0.23_fp;
    ev1.Y = -23.21_fp;

    ev2 = -ev1;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);
    REQUIRE(ev2.X == -0.23_fp);
    REQUIRE(ev2.Y == 23.21_fp);
}

SCENARIO("EVector:: - minus operator"){
    EVector ev1, ev2, ev3;

    ev1.X = 0.23_fp;
    ev1.Y = -23.21_fp;

    ev2.X = 4.23_fp;
    ev2.Y = 43.21_fp;


    ev3 = ev2 - ev1;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);

    REQUIRE(ev2.X == 4.23_fp);
    REQUIRE(ev2.Y == 43.21_fp);

    REQUIRE(ev3.X == 4.00_fp);
    REQUIRE(ev3.Y == 66.42_fp);
}


SCENARIO("EVector:: + operator"){
    EVector ev1, ev2, ev3;

    ev1.X = 0.23_fp;
    ev1.Y = -23.21_fp;

    ev2.X = 4.23_fp;
    ev2.Y = 43.21_fp;


    ev3 = ev2 + ev1;

    REQUIRE(ev1.X == 0.23_fp);
    REQUIRE(ev1.Y == -23.21_fp);

    REQUIRE(ev2.X == 4.23_fp);
    REQUIRE(ev2.Y == 43.21_fp);

    REQUIRE(ev3.X == 4.46_fp);
    REQUIRE(ev3.Y == 20.00_fp);
}



