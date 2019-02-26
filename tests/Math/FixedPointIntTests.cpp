#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;

SCENARIO("FixedPointInt::Constructor: Defaults to 0"){
    FixedPointInt fp;
    REQUIRE(fp.Value == 0);
}

SCENARIO("FixedPointInt::SetValueFromDouble: "){
    FixedPointInt fp;
    REQUIRE(fp.Value == 0);

    // need to test
    REQUIRE(true == false);
}




SCENARIO("FixedPointInt::Constructor(FixedPointInt)"){
    FixedPointInt fpi(1.0_fp);
    REQUIRE(fpi.Value == 100);

    FixedPointInt fpi2(-1.0_fp);
    REQUIRE(fpi2.Value == -100);


    FixedPointInt fpi3(31.33_fp);
    REQUIRE(fpi3.Value == 3133);
}

