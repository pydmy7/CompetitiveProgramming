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

std::int64_t sqrt(std::int64_t n) {
    std::int64_t s = std::sqrt(n);
    while (s * s > n) {
        --s;
    }
    while ((s + 1) * (s + 1) <= n) {
        ++s;
    }
    return s;
}

template <std::floating_point T>
bool isEqual(T a, T b, T eps = std::numeric_limits<T>::epsilon() * 100) {
    if (a == b) {
        return true;
    }
    if (std::isnan(a) || std::isnan(b) || std::isinf(a) || std::isinf(b)) {
        return false;
    }
    return std::abs(a - b) <= eps * std::max({T{1}, std::abs(a), std::abs(b)});
}

std::array<std::vector<int>, 3> eulerSieve(int n) {
    std::vector<int> minPrimeFactor(n  + 1, 0);
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
