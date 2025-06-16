#pragma once

#include <iterator>
#include <vector>

auto mergeSort(auto begin, auto end, auto && comp) -> void {
    if (std::distance(begin, end) < 2) {
        return;
    }

    auto mid {std::next(begin, std::distance(begin, end) >> 1)};

    mergeSort(begin, mid);
    mergeSort(mid, end);

    if (comp(*mid, *std::prev(mid))) {
        std::vector<typename std::iterator_traits<decltype(begin)>::value_type> tmp;

        for (auto mover {begin}; mover != end; ++mover) {
            tmp.emplace_back(*mover);
        }

        auto leftBegin {tmp.begin()};
        auto rightBegin {std::next(tmp.begin(), std::distance(tmp.begin(), tmp.end()) >> 1)};
        auto leftEnd {rightBegin};
        auto rightEnd {tmp.end()};

        for (auto mover {begin}; mover != end; ++mover) {
            if (leftBegin == leftEnd) {
                *mover = std::move(*rightBegin);

                ++rightBegin;
            } else if (rightBegin == rightEnd) {
                *mover = std::move(*leftBegin);

                ++leftBegin;
            } else {
                if (comp(*leftBegin, *rightBegin)) {
                    *mover = std::move(*leftBegin);

                    ++leftBegin;
                } else {
                    *mover = std::move(*rightBegin);

                    ++rightBegin;
                }
            }
        }
    }
}