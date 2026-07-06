#pragma once

#include <cmath>
#include <cstdint>
#include <concepts>
#include <array>
#include <vector>

namespace scl {

using i64 = std::int64_t;

i64 ceilDiv(i64 n, i64 m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    } else {
        return n / m;
    }
}

i64 floorDiv(i64 n, i64 m) {
    if (n >= 0) {
        return n / m;
    } else {
        return (n - m + 1) / m;
    }
}

template <std::floating_point T>
bool isNearlyEqual(T value, T expected, T eps = std::numeric_limits<T>::epsilon() * 100) {
    if (value == expected) {
        return true;
    }
    if (std::isnan(value) || std::isnan(expected) || std::isinf(value) || std::isinf(expected)) {
        return false;
    }
    return std::abs(value - expected) <= eps * std::max({T{1}, std::abs(expected)});
}

std::array<std::vector<int>, 3> eulerSieve(int n) {
    std::vector<int> minPrimeFactor(n + 1, 0);
    std::vector<int> primes;
    std::vector<int> phi(n + 1);
    phi[1] = 1;

    for (auto i = 2; i <= n; ++i) {
        if (minPrimeFactor[i] == 0) {
            minPrimeFactor[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }

        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minPrimeFactor[i * p] = p;
            if (p == minPrimeFactor[i]) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }

    return { minPrimeFactor, primes, phi };
}

}  // namespace scl
