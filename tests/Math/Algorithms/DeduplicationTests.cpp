#include "catch.hpp"
#include <memory>

#include "Algorithms/Deduplication.h"
#include "FixedPointInt.h"

using namespace SGE_Math_Algorithms;
using namespace SGE_Math;



SCENARIO("Deduplication::Unique: [1.01_fp, 2.01_fp, 1.01_fp] returns [1.01_fp, 2.0_fp]"){
    std::vector<FixedPointInt> a = {1.01_fp, 2.01_fp, 1.01_fp};

    Deduplication::Unique(a);

    std::vector<FixedPointInt> expectedValues = {1.01_fp, 2.0_fp};

    REQUIRE(a.size() == expectedValues.size());

    REQUIRE(a[0].Value == (1.01_fp).Value);
    REQUIRE(a[1].Value == (2.01_fp).Value);
}


SCENARIO("Deduplication::Unique: [1,0,-1,1,1] returns [1,0,-1]"){
    std::vector<int> a = {1,0,-1,1,1};

    Deduplication::Unique(a);

    std::vector<int> expectedValues = {-1, 0, 1};

    REQUIRE(a.size() == expectedValues.size());

    REQUIRE(a[0] == expectedValues[0]);
    REQUIRE(a[1] == expectedValues[1]);
    REQUIRE(a[2] == expectedValues[2]);
}


SCENARIO("Deduplication::Unique: [21,0,-1,10,1,21,10,0,0] returns [-1,0,1,10,21]"){
    std::vector<int> a = {21,0,-1,10,1,21,10,0,0};

    Deduplication::Unique(a);

    std::vector<int> expectedValues = {-1,0,1,10,21};

    REQUIRE(a.size() == expectedValues.size());

    REQUIRE(a[0] == expectedValues[0]);
    REQUIRE(a[1] == expectedValues[1]);
    REQUIRE(a[2] == expectedValues[2]);
    REQUIRE(a[3] == expectedValues[3]);
    REQUIRE(a[4] == expectedValues[4]);
}

