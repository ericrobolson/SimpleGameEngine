#include "catch.hpp"
#include "FixedPointInt.h"
#include <limits>

using namespace SGE_Math;

const int MININTSIZE = std::numeric_limits<int>::min();
const int MAXINTSIZE = std::numeric_limits<int>::max();

const int _decimalPlaces = 2;
const int _valuesPerDecimal = 10;
const int _scalingFactor = _valuesPerDecimal * _valuesPerDecimal; // (10^decimalPlaces), as this contains 2 decimal places, scale ints/floats by this value to get them
const int _halfScalingFactor = _scalingFactor/2;


SCENARIO("FixedPointInt::Constructor: Defaults to 0"){
    FixedPointInt fp;
    REQUIRE(fp.Value == 0);
}

SCENARIO("FixedPointInt::Constructor(decimal)"){


    // integer checks
    FixedPointInt fpi(1.0_fp);
    REQUIRE(fpi.Value == 100);

    FixedPointInt fpi2(-1.0_fp);
    REQUIRE(fpi2.Value == -100);
/*
    FixedPointInt fpi3((float)401);
    REQUIRE(fpi3.Value == 40100);

    FixedPointInt fpi4((float)-301);
    REQUIRE(fpi4.Value == -30100);

    // decimal checks
    FixedPointInt fpd((float).12);
    REQUIRE(fpd.Value == 12);

    FixedPointInt fpd2((float)-.12);
    REQUIRE(fpd2.Value == -12);

    FixedPointInt fpd3((float)4.01);
    REQUIRE(fpd3.Value == 401);

    FixedPointInt fpd4((float)-3.01);
    REQUIRE(fpd4.Value == -301);

    // decimal rounding checks
    FixedPointInt fpdr((float).125);
    REQUIRE(fpd.Value == 13);

    FixedPointInt fpdr1((float).124);
    REQUIRE(fpdr1.Value == 12);

    FixedPointInt fpdr2((float).124444445);
    REQUIRE(fpdr2.Value == 13);

    FixedPointInt fpdr3((float).124444444);
    REQUIRE(fpdr3.Value == 12);

    //todo: negative rounding checks
*/


    /*
    // Overflow checks
    int overflowValue = (MAXINTSIZE / _scalingFactor) + 1;

    FixedPointInt fpOf((int)overflowValue);
    REQUIRE(fpOf.Value == MAXINTSIZE);

    // Underflow checks
    int underflowValue = (MININTSIZE / _scalingFactor) - 1;

    FixedPointInt fpUf((int)underflowValue);
    REQUIRE(fpUf.Value == MININTSIZE);
    */
}

/*
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
*/
