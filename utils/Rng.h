#ifndef RNG_H
#define RNG_H

#include <random>
#include <array>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace Rng {
    inline std::mt19937& get_engine() {
        static std::mt19937 engine = []() {
            std::random_device rd;
            std::array<std::uint_least32_t, std::mt19937::state_size> seed_data{};
            std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
            std::seed_seq seq(seed_data.begin(), seed_data.end());
            return std::mt19937(seq);
        }();
        return engine;
    }

    inline void seed(std::uint_least32_t value) {
        get_engine().seed(value);
    }

    inline void seed_random() {
        std::random_device rd;
        std::array<std::uint_least32_t, std::mt19937::state_size> seed_data{};
        std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
        std::seed_seq seq(seed_data.begin(), seed_data.end());
        get_engine().seed(seq);
    }

    inline int generate_random_number(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(get_engine());
    }

    inline bool check_chance(int percentage) {
        if (percentage <= 0) return false;
        if (percentage >= 100) return true;
        return generate_random_number(1, 100) <= percentage;
    }
}

#endif // RNG_H