#include "catch.hpp"
#include "RandomNumberGenerator.h"
using namespace SGE;



SCENARIO("RandomNumberGenerator::Ctor"){
    RandomNumberGenerator& instance = RandomNumberGenerator::Instance();
    REQUIRE(instance.GetSeed() == 0);
}


SCENARIO("RandomNumberGenerator::Seed"){
    RandomNumberGenerator& instance = RandomNumberGenerator::Instance();

    int seed = 4;
    instance.Seed(seed);

    REQUIRE(instance.GetSeed() == seed);
}


SCENARIO("RandomNumberGenerator::RandomInt"){
    RandomNumberGenerator& instance = RandomNumberGenerator::Instance();

    int seed = 4;
    instance.Seed(seed);

    int expectedRng = 1081476;
    int actualRng = instance.RandomInt();

    REQUIRE(expectedRng == actualRng);

    expectedRng = 268507140;
    actualRng = instance.RandomInt();

    REQUIRE(expectedRng == actualRng);

    expectedRng = 1395765508;
    actualRng = instance.RandomInt();

    REQUIRE(expectedRng == actualRng);
}

SCENARIO("RandomNumberGenerator::RandomInt_WithRange"){
    RandomNumberGenerator& instance = RandomNumberGenerator::Instance();

    int seed = 5;
    instance.Seed(seed);

    // Note, possible edge case with 0 as the lower bounds

    int expectedRng = 0;
    int actualRng = instance.RandomInt(0,3);

    REQUIRE(expectedRng == actualRng);

    expectedRng = 1;
    actualRng = instance.RandomInt(0,3);

    REQUIRE(expectedRng == actualRng);

    expectedRng = 2;
    actualRng = instance.RandomInt(0,3);

    REQUIRE(expectedRng == actualRng);


    instance.Seed(10100);

    expectedRng = 88;
    actualRng = instance.RandomInt(0,100);

    REQUIRE(expectedRng == actualRng);
}
