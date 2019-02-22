#include "catch.hpp"
#include "DeterministicMath.h"

using namespace SGE_Math;


SCENARIO("FixedPointInt::Constructor: Defaults to 0"){
    FixedPointInt fp;
    REQUIRE((int)fp == 0);
    REQUIRE((float)fp == 0);
}

SCENARIO("FixedPointInt::Prefix ++: Adds 1"){
    FixedPointInt fp;
    ++fp;
    REQUIRE((int)fp == 1);
    REQUIRE((float)fp == (float)1.0);

    ++fp;
    REQUIRE((int)fp == 2);
    REQUIRE((float)fp == (float)2.0);
}

SCENARIO("FixedPointInt::Prefix -- Subtracts 1"){
    FixedPointInt fp;
    --fp;
    REQUIRE((int)fp == -1);
    REQUIRE((float)fp == (float)-1.0);

    --fp;
    REQUIRE((int)fp == -2);
    REQUIRE((float)fp == (float)-2.0);
}
