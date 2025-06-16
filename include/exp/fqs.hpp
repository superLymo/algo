#pragma once

#include <iterator>

auto quickSort(auto begin, auto end, auto && comp) -> void {
    if (std::distance(begin, end) < 2) {
        return;
    }

    auto savers {std::make_pair(std::next(begin), std::prev(end))};

    auto mover {std::next(begin)};

    while (mover != std::next(savers.second)) {
        if (comp(*mover, *begin)) {
            std::swap(*mover, *savers.first);

            ++savers.first;

            ++mover;
        } else if (comp(*begin, *mover)) {
            std::swap(*mover, * savers.second);

            --savers.second;
        } else {
            ++mover;
        }
    }

    std::swap(*begin, *std::prev(savers.first));

    quickSort(begin, std::prev(savers.first), comp);
    quickSort(std::next(savers.second), end, comp);
}