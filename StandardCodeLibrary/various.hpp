#pragma once

#include <cmath>
#include <cstdint>
#include <concepts>

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
    return std::abs(a - b) <= eps * std::max({T{1}, std::abs(a), std::abs(b)});
}

}  // namespace scl
