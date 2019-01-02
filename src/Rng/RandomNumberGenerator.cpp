#include "RandomNumberGenerator.h"
#include "Debugger.h"
using namespace SGE;

RandomNumberGenerator::RandomNumberGenerator()
{
    _seed = 0;
}

RandomNumberGenerator::~RandomNumberGenerator()
{
    //dtor
}

void RandomNumberGenerator::Seed(int i){
    _seed = i;
    _seeded = true;
}

int RandomNumberGenerator::xorshift32(int i){
    // https://en.wikipedia.org/wiki/Xorshift
    int x = i;

    x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;

    _seed = x;

    return x;
}

int RandomNumberGenerator::GetSeed(){
    return _seed;
}

int RandomNumberGenerator::RandomInt(){
    if (!_seeded){
        Debugger::Instance().ThrowException("Please set a seed.");
    }

    return xorshift32(_seed);
}

int RandomNumberGenerator::RandomInt(int minValue, int maxValue){
    int randomInt = 0;
    int value = 0;

    do{
        randomInt = RandomInt();
        value = randomInt % (maxValue + 1 - minValue) + minValue;
    } while(value < minValue || value > maxValue);

    return value;
}

