#pragma once

#include <iterator>

auto bs(auto begin, auto end, auto const & target) {
    while (begin != end) {
        auto mid {std::ranges::next(begin, std::ranges::distance(begin, end) >> 1)};

        if (*mid < target) {
            begin = std::next(mid);
        } else if (target < *mid) {
            end = mid;
        } else {
            return mid;
        }
    }

    return decltype(begin) {};
}

namespace exp__ {
    auto bs(auto begin, auto end, auto const & target) {
        while (begin != end) {
            auto mid {std::next(begin, std::distance(begin, end) >> 1)};

            if (target < *mid) {
                end = mid;
            } else if (*mid < target) {
                begin = std::next(mid);
            } else {
                return mid;
            }
        }

        return decltype(begin) {};
    }
}