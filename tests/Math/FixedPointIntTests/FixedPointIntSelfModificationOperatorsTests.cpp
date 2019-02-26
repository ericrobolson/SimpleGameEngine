#include "catch.hpp"
#include "FixedPointInt.h"
using namespace SGE_Math;


SCENARIO("FixedPointInt:: prefix ++"){
    FixedPointInt fp1;

    fp1 = 1.02_fp;
    ++fp1;

    REQUIRE(fp1 == 2.02_fp);

    fp1.Value = fp1.MAXVALUE;
    ++fp1;

    REQUIRE(fp1.Value == fp1.MAXVALUE);
}


SCENARIO("FixedPointInt:: prefix --"){
    FixedPointInt fp1;

    fp1 = 1.02_fp;
    --fp1;

    REQUIRE(fp1 == 0.02_fp);

    fp1 = -1.02_fp;
    --fp1;

    REQUIRE(fp1 == -2.02_fp);


    fp1.Value = fp1.MINVALUE;
    --fp1;

    REQUIRE(fp1.Value == fp1.MINVALUE);
}


SCENARIO("FixedPointInt:: +="){
    FixedPointInt fp1, fp2;

    fp1 = 1.02_fp;
    fp2 = 2.02_fp;

    fp1 += fp2;

    REQUIRE(fp1 == 3.04_fp);
    REQUIRE(fp2 == 2.02_fp);


    fp1.Value = fp1.MINVALUE;
    fp2 = -2.02_fp;

    fp1 += fp2;

    REQUIRE(fp1.Value == fp1.MINVALUE);
    REQUIRE(fp2 == -2.02_fp);

}


SCENARIO("FixedPointInt:: -="){
    FixedPointInt fp1, fp2;

    fp1 = 1.02_fp;
    fp2 = 2.02_fp;

    fp1 -= fp2;

    REQUIRE(fp1 == -1.0_fp);
    REQUIRE(fp2 == 2.02_fp);

    fp1.Value = fp1.MINVALUE;
    fp2 = 2.02_fp;

    fp1 -= fp2;

    REQUIRE(fp1.Value == fp1.MINVALUE);
    REQUIRE(fp2 == 2.02_fp);

}


SCENARIO("FixedPointInt:: *="){
    FixedPointInt fp1, fp2;

    fp1 = 1.02_fp;
    fp2 = 2.02_fp;

    fp1 *= fp2;

    REQUIRE(fp1 == 2.06_fp);
    REQUIRE(fp2 == 2.02_fp);

    fp1.Value = fp1.MINVALUE;
    fp2 = 2.02_fp;

    fp1 *= fp2;

    REQUIRE(fp1.Value == fp1.MINVALUE);
    REQUIRE(fp2 == 2.02_fp);

    fp1 = 0.0_fp;
    fp2 = 2.02_fp;

    fp1 *= fp2;

    REQUIRE(fp1 == 0.0_fp);
    REQUIRE(fp2 == 2.02_fp);

}




SCENARIO("FixedPointInt:: /="){
    FixedPointInt fp1, fp2;

    fp1 = 1.02_fp;
    fp2 = 2.02_fp;

    fp1 /= fp2;

    REQUIRE(fp1 == 0.51_fp);
    REQUIRE(fp2 == 2.02_fp);

    fp1 = 1.00_fp;
    fp2 = 3.0_fp;

    fp1 /= fp2;

    REQUIRE(fp1 == 0.33_fp);
    REQUIRE(fp2 == 3.0_fp);

    fp1 = 0.0_fp;
    fp2 = 2.02_fp;

    fp1 *= fp2;

    REQUIRE(fp1 == 0.0_fp);
    REQUIRE(fp2 == 2.02_fp);

}
