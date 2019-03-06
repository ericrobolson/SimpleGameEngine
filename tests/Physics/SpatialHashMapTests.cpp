#include "catch.hpp"
#include "SpatialHashMap.h"

#include "EVector.h"

using namespace SGE_Math;
using namespace SGE_Physics;

SCENARIO("SpatialHashMap:: Constructor"){

    SpatialHashMap shm(2.0_fp, 2.0_fp, 1.0_fp);

    REQUIRE(true == true);

}


SCENARIO("SpatialHashMap::HashEVector"){

    SpatialHashMap shm(2.0_fp, 2.0_fp, 1.0_fp);

    EVector ev;


}
