#pragma once

#include <iterator>

auto insertionSort(auto begin, auto end, auto && comp) -> void {
    if (std::distance(begin, end) < 2) {
        return;
    }

    for (auto mover {std::next(begin)}; mover != end; ++mover) {
        auto tmp {std::move(*mover)};
        auto finalPos {mover};

        while (finalPos != begin) {
            if (comp(tmp, *std::prev(finalPos))) {
                *finalPos = std::move(*std::prev(finalPos));

                std::advance(finalPos, -1);
            } else {
                break;
            }
        }

        *finalPos = std::move(tmp);
    }
}