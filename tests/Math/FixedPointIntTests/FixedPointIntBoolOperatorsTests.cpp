#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;



SCENARIO("FixedPointInt:: >="){
    FixedPointInt fp1, fp2;

    // pos int test
    // pos decimal test
    // neg int test
    // neg decimal test

    // lt
    // eq

    // fp1 > fp2
    fp1 = 10;
    fp2 = 9;
    REQUIRE((fp1 >= fp2) == true);
/*
    fp1 = (FixedPointInt).02;
    fp2 = (FixedPointInt).01;
    REQUIRE((fp1 >= fp2) == true);

    fp1 = -2;
    fp2 = -3;
    REQUIRE((fp1 >= fp2) == true);

    fp1 = -.01;
    fp2 = -.02;
    REQUIRE((fp1 >= fp2) == true);

    // fp1 < fp2
    fp1 = 101;
    fp2 = 900;
    REQUIRE((fp1 >= fp2) == false);

    fp1 = 1.02;
    fp2 = 1.03;
    REQUIRE((fp1 >= fp2) == false);

    fp1 = -4;
    fp2 = -3;
    REQUIRE((fp1 >= fp2) == false);

    fp1 = -4.01;
    fp2 = -3.02;
    REQUIRE((fp1 >= fp2) == false);
*/

}
