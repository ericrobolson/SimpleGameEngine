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


SCENARIO("FixedPointInt:: plus +"){
    FixedPointInt fp1, fp2, fp3;

    // positive + positive
    fp1.Value = 4;
    fp2.Value = 3;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == 4);
    REQUIRE(fp2.Value == 3);
    REQUIRE(fp3.Value == 7);

    // positive + negative
    fp1.Value = 4;
    fp2.Value = -3;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == 4);
    REQUIRE(fp2.Value == -3);
    REQUIRE(fp3.Value == 1);

    // positive + positive overflow check
    fp1.Value = fp2.MAXVALUE;
    fp2.Value = fp2.MAXVALUE;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == fp1.MAXVALUE);
    REQUIRE(fp2.Value == fp1.MAXVALUE);
    REQUIRE(fp3.Value == fp1.MAXVALUE);

    // negative + positive
    fp1.Value = -4;
    fp2.Value = 3;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == -4);
    REQUIRE(fp2.Value == 3);
    REQUIRE(fp3.Value == -1);


    // negative + negative
    fp1.Value = -4;
    fp2.Value = -5;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == -4);
    REQUIRE(fp2.Value == -5);
    REQUIRE(fp3.Value == -9);

    // negative + negative overflow check
    fp1.Value = fp2.MINVALUE;
    fp2.Value = fp2.MINVALUE + 1;

    fp3 = fp1 + fp2;

    REQUIRE(fp1.Value == fp1.MINVALUE);
    REQUIRE(fp2.Value == (fp2.MINVALUE + 1));
    REQUIRE(fp3.Value == fp1.MINVALUE);
}

SCENARIO("FixedPointInt:: multiplication *"){
    FixedPointInt fp1, fp2, fp3;

    // positive int * zero
    fp1.Value = 400;
    fp2.Value = 0;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 0);
    REQUIRE(fp3.Value == 0);

    // positive int * -1
    fp1.Value = 400;
    fp2.Value = -100;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == -100);
    REQUIRE(fp3.Value == -400);

    // positive int * 1
    fp1.Value = 400;
    fp2.Value = 100;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 100);
    REQUIRE(fp3.Value == 400);


    // positive int * positive int
    fp1.Value = 400;
    fp2.Value = 200;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 200);
    REQUIRE(fp3.Value == 800);

    // positive int * positive decimal < 1
    fp1.Value = 400;
    fp2.Value = 15;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 15);
    REQUIRE(fp3.Value == 60);

    fp1.Value = 400;
    fp2.Value = 16;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 16);
    REQUIRE(fp3.Value == 64);

    fp1.Value = 400;
    fp2.Value = 4;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 4);
    REQUIRE(fp3.Value == 16);

    // positive int * positive decimal > 1
    fp1.Value = 800;
    fp2.Value = 115;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 800);
    REQUIRE(fp2.Value == 115);
    REQUIRE(fp3.Value == 920);

    fp1.Value = 800;
    fp2.Value = 116;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 800);
    REQUIRE(fp2.Value == 116);
    REQUIRE(fp3.Value == 928);

    fp1.Value = 400;
    fp2.Value = 401;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 400);
    REQUIRE(fp2.Value == 401);
    REQUIRE(fp3.Value == 1604);

    // positive int * positive int overflow
    fp1.Value = 800;
    fp2.Value = fp2.MAXVALUE;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 800);
    REQUIRE(fp2.Value == fp1.MAXVALUE);
    REQUIRE(fp3.Value == fp2.MAXVALUE);

    // positive int (max) * decimal < 1 doesn't overflow
    fp1.Value = fp2.MAXVALUE;
    fp2.Value = 99;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == fp2.MAXVALUE);
    REQUIRE(fp2.Value == 99);
    REQUIRE(fp3.Value == 2126008811); // (2147483647 * 99) / 100 = 2126008810.53 rounds to 2126008811


    // positive int (max) * decimal > 1 max value
    fp1.Value = fp2.MAXVALUE;
    fp2.Value = 101;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == fp2.MAXVALUE);
    REQUIRE(fp2.Value == 101);
    REQUIRE(fp3.Value == fp2.MAXVALUE);

    // positive decimal < 1 * zero
    fp1.Value = 99;
    fp2.Value = 0;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 99);
    REQUIRE(fp2.Value == 0);
    REQUIRE(fp3.Value == 0);


    // positive decimal < 1 * positive int
    fp1.Value = 99;
    fp2.Value = 200;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 99);
    REQUIRE(fp2.Value == 200);
    REQUIRE(fp3.Value == 198);

    // positive decimal < 1 * positive decimal < 1
    fp1.Value = 99;
    fp2.Value = 99;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 99);
    REQUIRE(fp2.Value == 99);
    REQUIRE(fp3.Value == 98); // 99 * 99 / 100 = 98.01

    fp1.Value = 99;
    fp2.Value = 2;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 99);
    REQUIRE(fp2.Value == 2);
    REQUIRE(fp3.Value == 2); // 99 * 2 / 100 = 1.98


    fp1.Value = 99;
    fp2.Value = 1;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 99);
    REQUIRE(fp2.Value == 1);
    REQUIRE(fp3.Value == 1); // 99 * 1 / 100 = .99

    fp1.Value = 6;
    fp2.Value = 3;

    fp3 = fp1 * fp2;

    REQUIRE(fp1.Value == 6);
    REQUIRE(fp2.Value == 3);
    REQUIRE(fp3.Value == 0); // 6* 3 / 100 = .18

    // positive decimal < 1 * positive decimal > 1
    // positive decimal < 1 * positive int overflow
    // positive decimal < 1* positive decimal overflow
    // positive decimal > 1 * zero
    // positive decimal > 1 * positive int
    // positive decimal > 1 * positive decimal < 1
    // positive decimal > 1 * positive decimal > 1
    // positive decimal > 1 * positive int overflow
    // positive decimal > 1* positive decimal overflow

    // todo:
    // refactor out things to make it better? e.g. theory type
    // positive * negative
    // negative * positive
    // negative * negative

    // test cases positive * positive:
    // positive int * zero
    // positive int * -1
    // positive int * 1
    // positive int * positive int
    // positive int * positive decimal < 1
    // positive int * positive decimal > 1
    // positive int * positive int overflow
    // positive int (max) * decimal < 1 doesn't overflow
    // positive int (max) * decimal > 1 max value
    // positive decimal < 1 * zero
    // positive decimal < 1 * positive int
    // positive decimal < 1 * positive decimal > 1







}
