#pragma once

#include <random>
#include <type_traits>

namespace scl {

template <typename T>
struct Random {
    static T get(T lo, T hi) {
        static std::mt19937 rng{ std::random_device{}() };

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(lo, hi);
            return dist(rng);
        }
        else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(lo, hi);
            return dist(rng);
        }
        else {
            static_assert(std::is_arithmetic_v<T>, "Random<T> only supports arithmetic types");
        }
    }
};

}  // namespace scl
