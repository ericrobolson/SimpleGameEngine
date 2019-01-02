#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

namespace SGE{

    /// A deterministic RNG
    class RandomNumberGenerator
    {
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

            int _seed = 0;
            bool _seeded = false;
    };
}


#endif // RANDOMNUMBERGENERATOR_H
