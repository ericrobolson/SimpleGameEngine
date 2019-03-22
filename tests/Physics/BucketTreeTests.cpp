#include "catch.hpp"
#include "FixedPointInt.h"
#include "EVector.h"
#include "BucketTree.h"
using namespace SGE_Physics;

SCENARIO("BucketTree: Constructor: No children"){
    EVector ev1, ev2;

    ev1.X = 0.0_fp;
    ev1.Y = -1.0_fp;

    ev2.X = 2.0_fp;
    ev2.Y = 3.0_fp;

    // No children
    BucketTree bt(0, ev1, ev2);

    REQUIRE(bt.NeBucketTreePtr == nullptr);
    REQUIRE(bt.NwBucketTreePtr == nullptr);
    REQUIRE(bt.SeBucketTreePtr == nullptr);
    REQUIRE(bt.SwBucketTreePtr == nullptr);

    REQUIRE(bt.GetMinCoordinate().X == ev1.X);
    REQUIRE(bt.GetMinCoordinate().Y == ev1.Y);

    REQUIRE(bt.GetMaxCoordinate().X == ev2.X);
    REQUIRE(bt.GetMaxCoordinate().Y == ev2.Y);


    // Negative levels means no children
    BucketTree bt2(-23, ev1, ev2);

    REQUIRE(bt2.NeBucketTreePtr == nullptr);
    REQUIRE(bt2.NwBucketTreePtr == nullptr);
    REQUIRE(bt2.SeBucketTreePtr == nullptr);
    REQUIRE(bt2.SwBucketTreePtr == nullptr);

    REQUIRE(bt2.GetMinCoordinate().X == ev1.X);
    REQUIRE(bt2.GetMinCoordinate().Y == ev1.Y);

    REQUIRE(bt2.GetMaxCoordinate().X == ev2.X);
    REQUIRE(bt2.GetMaxCoordinate().Y == ev2.Y);
}

SCENARIO("BucketTree: Constructor: Reorders vectors for consistent min and max"){
    EVector ev1, ev2;

    ev1.X = 0.0_fp;
    ev1.Y = -1.0_fp;

    ev2.X = -2.0_fp;
    ev2.Y = -3.0_fp;

    BucketTree bt(0, ev1, ev2);

    REQUIRE(bt.NeBucketTreePtr == nullptr);
    REQUIRE(bt.NwBucketTreePtr == nullptr);
    REQUIRE(bt.SeBucketTreePtr == nullptr);
    REQUIRE(bt.SwBucketTreePtr == nullptr);

    REQUIRE(bt.GetMinCoordinate().X == ev2.X);
    REQUIRE(bt.GetMinCoordinate().Y == ev2.Y);

    REQUIRE(bt.GetMaxCoordinate().X == ev1.X);
    REQUIRE(bt.GetMaxCoordinate().Y == ev1.Y);


    ev1.X = 10.0_fp;
    ev1.Y = 1.0_fp;

    ev2.X = 12.0_fp;
    ev2.Y = -3.0_fp;

    BucketTree bt2(-23, ev1, ev2);

    REQUIRE(bt2.NeBucketTreePtr == nullptr);
    REQUIRE(bt2.NwBucketTreePtr == nullptr);
    REQUIRE(bt2.SeBucketTreePtr == nullptr);
    REQUIRE(bt2.SwBucketTreePtr == nullptr);

    REQUIRE(bt2.GetMinCoordinate().X == ev1.X);
    REQUIRE(bt2.GetMinCoordinate().Y == ev2.Y);

    REQUIRE(bt2.GetMaxCoordinate().X == ev2.X);
    REQUIRE(bt2.GetMaxCoordinate().Y == ev1.Y);
}
