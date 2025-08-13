#include <initializer_list>
#include <print>
#include <algorithm>
#include <cmath>

#include "binary/binarySearch.hpp"

template <uint64_t wholeNumber>
struct adder__ {
    static constexpr uint64_t value {(wholeNumber % 10) + adder__<wholeNumber / 10>::value};
};

template <>
struct adder__<0> {
    static constexpr uint64_t value {0};
};

template <uint64_t numberLimit>
struct adder {
    static constexpr uint64_t value {adder__<numberLimit>::value + adder<numberLimit - 1>::value};
};

template <>
struct adder<0> {
    static constexpr uint64_t value {0};
};


auto testMain() -> int {
    std::println("{}", adder<12>::value);

    return 0;
}