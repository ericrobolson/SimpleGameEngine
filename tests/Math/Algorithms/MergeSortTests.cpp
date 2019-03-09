
#include "catch.hpp"
#include <memory>

#include "Algorithms/MergeSort.h"

using namespace SGE_Math_Algorithms;

SCENARIO("MergeSort::MergeSort: [1,0,-1] returns [-1,0,1]"){
    std::vector<int> a = {1, 0, -1};

    MergeSort::Sort(a);

    std::vector<int> expectedValues = {-1, 0, 1};

    REQUIRE(a[0] == expectedValues[0]);
    REQUIRE(a[1] == expectedValues[1]);
    REQUIRE(a[2] == expectedValues[2]);
}


SCENARIO("MergeSort::MergeSort: [1,0,-1,2,0,1] returns [-1,0,0,1,1,2]"){
    std::vector<int> a = {1,0,-1,2,0,1};

    MergeSort::Sort(a);

    std::vector<int> expectedValues = {-1,0,0,1,1,2};

    REQUIRE(a[0] == expectedValues[0]);
    REQUIRE(a[1] == expectedValues[1]);
    REQUIRE(a[2] == expectedValues[2]);
    REQUIRE(a[3] == expectedValues[3]);
    REQUIRE(a[4] == expectedValues[4]);
    REQUIRE(a[5] == expectedValues[5]);
}


SCENARIO("MergeSort::MergeSort: [1] returns [1]"){
    std::vector<int> a = {1};

    MergeSort::Sort(a);

    std::vector<int> expectedValues = {1};

    REQUIRE(a[0] == expectedValues[0]);
}



