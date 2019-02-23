#include "catch.hpp"
#include "FixedPointInt.h"

using namespace SGE_Math;


//todo: do all tests with decimals as well

SCENARIO("FixedPointInt::Constructor: Defaults to 0"){
    FixedPointInt fp;
    REQUIRE((int)fp == 0);
    REQUIRE((float)fp == 0);
}


SCENARIO("FixedPointInt::Assignment =(int): Creates int representation"){
    FixedPointInt fp;

    fp = 4;

    REQUIRE((float)fp == (float)4.00);
    REQUIRE((int)fp == (int)4);
}


SCENARIO("FixedPointInt::Assignment =(float): Creates float representation"){
    FixedPointInt fp;

    float expectedValue = 4;

    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)4);


    expectedValue = .05;
    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)0);


    expectedValue = .5;
    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)1);

    expectedValue = -.5;
    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)-1);

    expectedValue = -.4;
    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)0);




    expectedValue = -.6;
    fp = expectedValue;

    REQUIRE((float)fp == expectedValue);
    REQUIRE((int)fp == (int)-1);

    expectedValue = 44.445;
    fp = expectedValue;

    REQUIRE((float)fp == (float)44.45);
    REQUIRE((int)fp == (int)44);

    expectedValue = 44.499;
    fp = expectedValue;

    REQUIRE((float)fp == (float)44.45);
    REQUIRE((int)fp == (int)44);

}


SCENARIO("FixedPointInt::Assignment =(FixedPointInt): Copies FpInt"){
    FixedPointInt fp;
    fp = 4;

    FixedPointInt fp2;
    fp2 = fp;

    REQUIRE((float)fp2 == (float)4.00);
    REQUIRE((int)fp2 == (int)4);
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

SCENARIO("FixedPointInt:: += Adds to FixedPointInt"){
    FixedPointInt fp1, fp2;

    fp1 = -2;
    fp2 = 3;

    FixedPointInt value = (fp1 += fp2);

    REQUIRE((float)value == (float)1.0);
}

SCENARIO("FixedPointInt:: -= Subtracts to FixedPointInt"){
    FixedPointInt fp1, fp2;

    fp1 = -3;
    fp2 = 100;

    FixedPointInt value = (fp1 -= fp2);

    REQUIRE((float)value == (float)-103.0);
}


SCENARIO("FixedPointInt:: *= Multiplication to FixedPointInt"){
    FixedPointInt fp1, fp2;

    fp1 = 1;
    fp2 = 0;


    FixedPointInt value = (fp1 *= fp2);
    REQUIRE((float)value == (float)0.0);

    fp1 = 200;
    fp2 = 2;

    fp1 *= fp2;

    REQUIRE((float)fp1 == (float)400.0);

}
