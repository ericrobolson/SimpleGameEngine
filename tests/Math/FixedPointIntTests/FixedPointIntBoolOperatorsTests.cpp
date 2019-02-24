#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;

SCENARIO("FixedPointInt:: >="){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 >= fp2) == true);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 >= fp2) == false);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 >= fp2) == true);
}

SCENARIO("FixedPointInt:: <="){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 <= fp2) == true);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 <= fp2) == true);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 <= fp2) == false);
}


SCENARIO("FixedPointInt:: >"){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 > fp2) == false);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 > fp2) == false);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 > fp2) == true);
}


SCENARIO("FixedPointInt:: <"){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 < fp2) == false);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 < fp2) == true);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 < fp2) == false);
}

SCENARIO("FixedPointInt:: =="){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 == fp2) == true);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 == fp2) == false);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 == fp2) == false);
}

SCENARIO("FixedPointInt:: !="){
    FixedPointInt fp1;
    FixedPointInt fp2;

    // Equal to
    fp1.Value = 1;
    fp2.Value = 1;

    REQUIRE((fp1 != fp2) == false);

    // Less than
    fp1.Value = 1;
    fp2.Value = 2;

    REQUIRE((fp1 != fp2) == true);

    // Greater than
    fp1.Value = 2;
    fp2.Value = 1;

    REQUIRE((fp1 != fp2) == true);
}


