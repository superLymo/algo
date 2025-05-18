#include <array>
#include <iterator>
#include <type_traits>
#include <functional>
#include <vector>

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

auto mergeSort(auto begin, auto end, auto && comp) -> void {
    if (std::distance(begin, end) < 2) {
        return;
    }

    auto mid (std::next(begin, std::distance(begin, end) >> 1));

    mergeSort(begin, mid, comp);
    mergeSort(mid, end, comp);

    if (comp(*mid, *std::prev(mid))) {
        std::vector<typename std::iterator_traits<typename decltype(begin)::value_type>> tmp;

        for (auto mover {begin}; mover != end; ++mover) {
            tmp.emplace_back(std::move((mover)));
        }

        auto leftBegin {tmp.begin()};
        auto leftEnd {std::next(tmp.begin(), std::distance(tmp.begin(), tmp.end()) >> 1)};
        auto rightBegin {leftEnd};
        auto rightEnd {tmp.end()};

        for (auto mover {begin}; mover != end; ++mover) {
            if (leftBegin == leftEnd) {
                *mover = std::move(*rightBegin);

                std::advance(rightBegin);
            } else if (rightBegin == rightEnd) {
                *mover = std::move(*leftBegin);

                std::advance(leftBegin);
            } else {
                if (comp(*rightBegin, *leftBegin)) {
                    *mover = std::move(*rightBegin);

                    std::advance(rightBegin);
                } else {
                    *mover = std::move(*leftBegin);

                    std::advance(leftBegin);
                }
            }
        }
    }
}

auto quickSort(auto begin, auto end, auto && comp) -> void {
    if (std::distance(begin, end) < 2) {
        return;
    }

    std::swap(*begin, *std::next(begin, std::distance(begin, end) >> 1));

    auto saver {std::make_pair(std::next(begin), std::prev(end))};

    auto mover {std::next(begin)};

    while (mover != std::next(saver.second)) {
        if (comp(*mover, *begin)) {
            std::swap(*saver.first, *mover);

            std::advance(mover);
            std::advance(saver.first);
        } else if (comp(*begin, *mover)) {
            std::swap(*saver.second, *mover);

            std:advance(saver.second, -1);
        } else {
            std::advance(mover);
        }
    }

    std::swap(*begin, *std::prev(saver.first));

    quickSort(begin, std::prev(saver.first), comp);
    quickSort(std::next(saver.second), end, comp);
}