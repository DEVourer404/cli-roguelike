#ifndef RNG_H
#define RNG_H



#include <random>

namespace Rng {
    inline int generate_random_number(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);

        return distribution(gen);
    }
}

#endif // RNG_H