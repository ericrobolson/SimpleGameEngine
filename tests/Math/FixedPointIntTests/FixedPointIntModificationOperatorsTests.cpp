#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;


SCENARIO("FixedPointInt:: negative - operator"){
    FixedPointInt fp1;

    fp1.Value = 10000;

    FixedPointInt fp2 = -fp1;

    REQUIRE(fp1.Value == 10000);
    REQUIRE(fp2.Value == -10000);


    fp1.Value = -2;

    fp2 = -fp1;

    REQUIRE(fp1.Value == -2);
    REQUIRE(fp2.Value == 2);
}

SCENARIO("FixedPointInt:: minus -"){
    FixedPointInt fp1, fp2, fp3;

    // positive - positive
    fp1.Value = 4;
    fp2.Value = 3;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == 4);
    REQUIRE(fp2.Value == 3);
    REQUIRE(fp3.Value == 1);

    // positive - negative
    fp1.Value = 4;
    fp2.Value = -3;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == 4);
    REQUIRE(fp2.Value == -3);
    REQUIRE(fp3.Value == 7);

    // positive - negative overflow check
    fp1.Value = fp2.MAXVALUE;
    fp2.Value = fp2.MINVALUE;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == fp1.MAXVALUE);
    REQUIRE(fp2.Value == fp1.MINVALUE);
    REQUIRE(fp3.Value == fp1.MAXVALUE);

    // negative - positive
    fp1.Value = -4;
    fp2.Value = 3;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == -4);
    REQUIRE(fp2.Value == 3);
    REQUIRE(fp3.Value == -7);


    // negative - negative
    fp1.Value = -4;
    fp2.Value = -5;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == -4);
    REQUIRE(fp2.Value == -5);
    REQUIRE(fp3.Value == 1);

    // negative - negative overflow check
    fp1.Value = fp2.MINVALUE;
    fp2.Value = fp2.MINVALUE + 1;

    fp3 = fp1 - fp2;

    REQUIRE(fp1.Value == fp1.MINVALUE);
    REQUIRE(fp2.Value == (fp2.MINVALUE + 1));
    REQUIRE(fp3.Value == fp1.MINVALUE);
}

