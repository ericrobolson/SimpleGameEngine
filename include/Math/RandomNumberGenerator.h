#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

namespace SGE_Math{

class RandomNumberGenerator
{
   /// A deterministic RNG
    public:
    static RandomNumberGenerator& Instance(){
        static RandomNumberGenerator *instance = new RandomNumberGenerator();
        return *instance;
    };

    void Seed(int i);
    int GetSeed();

    int RandomInt();
    int RandomInt(int minValue, int maxValue);

    virtual ~RandomNumberGenerator();
    private:
    RandomNumberGenerator();

    int xorshift32(int i); // https://en.wikipedia.org/wiki/Xorshift

    int _seed = 1234;
};

}

#endif // RANDOMNUMBERGENERATOR_H
