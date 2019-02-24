#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;

SCENARIO("FixedPointInt:: ="){
    FixedPointInt fp1;
    FixedPointInt fp2;

    fp1.Value = 1;
    fp2.Value = 2;

    fp1 = fp2;

    REQUIRE(fp1.Value == 2);

    fp1.Value = 55;
    fp2.Value = 556;

    fp1 = fp2;
    REQUIRE(fp1.Value == 556);

    fp1 = fp1;
    REQUIRE(fp1.Value == 556);
}
