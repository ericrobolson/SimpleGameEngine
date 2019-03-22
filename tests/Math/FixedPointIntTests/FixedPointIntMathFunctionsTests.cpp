#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;

SCENARIO("FixedPointInt:: abs()"){
    FixedPointInt fp1, fp2;

    fp1 = 1.0_fp;

    fp2 = fp1.abs();


    REQUIRE(fp2 == 1.0_fp);
    REQUIRE(fp1 == 1.0_fp);

    fp1 = -1.0_fp;
    REQUIRE(fp1.abs() == 1.0_fp);
    REQUIRE(fp1 == -1.0_fp);

    fp1 = -21.1_fp;
    REQUIRE(fp1.abs() == 21.1_fp);
    REQUIRE(fp1 == -21.1_fp);
}

SCENARIO("FixedPointInt:: sqrt()"){
    //todo: need to implement
    FixedPointInt fp1;

    fp1 = 1.0_fp;
    REQUIRE(fp1.sqrt() == 1.0_fp);
    REQUIRE(fp1 == 1.0_fp);
    REQUIRE(true == false);
}

SCENARIO("FixedPointInt::min()"){
    FixedPointInt fp1, fp2, fp3;

    fp1 = 1.0_fp;
    fp2 = 2.0_fp;

    fp3 = FixedPointInt::minimum(fp1, fp2);

    REQUIRE(fp3.Value == fp1.Value);

    fp1 = 1.0_fp;
    fp2 = 1.0_fp;

    fp3 = FixedPointInt::minimum(fp1, fp2);

    REQUIRE(fp3.Value == fp1.Value);

    fp1 = 1.0_fp;
    fp2 = -1.0_fp;

    fp3 = FixedPointInt::minimum(fp1, fp2);

    REQUIRE(fp3.Value == fp2.Value);
}
