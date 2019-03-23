#include "catch.hpp"
#include "FixedPointInt.h"
#include <string>
using namespace SGE_Math;

SCENARIO("FixedPointInt:: (string)"){
    FixedPointInt fp1;

    fp1 = 2.09_fp;
    REQUIRE((std::string)fp1 == "2.09");

    fp1 = -2.09_fp;
    REQUIRE((std::string)fp1 == "-2.09");

    fp1 = 0.0_fp;
    REQUIRE((std::string)fp1 == "0.00");
}

SCENARIO("FixedPointInt:: (int)"){
    FixedPointInt fp1;

    // positive integers
    fp1.Value = 100;
    REQUIRE((int)fp1 == 1);

    fp1.Value = 44100;
    REQUIRE((int)fp1 == 441);

    // negative integers
    fp1.Value = -100;
    REQUIRE((int)fp1 == -1);

    fp1.Value = -56700;
    REQUIRE((int)fp1 == -567);

    // negative decimals
        // round down
    fp1.Value = -101;
    REQUIRE((int)fp1 == -1);

        // round down
    fp1.Value = -04;
    REQUIRE((int)fp1 == 0);

        // round up
    fp1.Value = -445;
    REQUIRE((int)fp1 == -5);


    // positive decimals
           // round up
    fp1.Value = 149;
    REQUIRE((int)fp1 == 2);

           // round down
    fp1.Value = 143;
    REQUIRE((int)fp1 == 1);

        // round down
    fp1.Value = 04;
    REQUIRE((int)fp1 == 0);

        // round up
    fp1.Value = 5445;
    REQUIRE((int)fp1 == 55);

}
