#pragma once

template <typename ItType, typename ValueType>
auto binarySearch(ItType begin, ItType end, ValueType const & target) -> ItType {
    if (end - begin < 1) {
        return ItType {};
    }

    while (begin != end) {
        ItType mid {((end - begin) >> 1) + begin};

        if (*mid < target) {
            begin = mid + 1;
        } else if (target < *mid) {
            end = mid;
        } else {
            return mid;
        }
    }

    return ItType {};
}