#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>

template <typename eleType, typename compType = std::less<eleType>>
class myHeap {
    std::vector<eleType> data;
    compType comp;

    auto shiftUp(std::size_t index) -> void {
        eleType tmp {std::move(data[index])};

        while (index != 0) {
            if (comp(tmp, data[(index - 1) >> 1])) {
                data[index] = std::move(data[(index - 1) >> 1]);

                index = (index - 1) >> 1;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }

    auto shiftDown(std::size_t index) -> void {
        eleType tmp {std::move(data[index])};

        while ((index << 1) + 1 < data.size()) {
            std::size_t minSon {(index << 1) + 1};

            if (minSon + 1 < data.size() && comp(data[minSon + 1], data[minSon])) {
                ++minSon;
            }

            if (comp(data[minSon], tmp)) {
                data[index] = std::move(data[minSon]);

                index = minSon;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }
public:
    explicit
    myHeap(compType && comp__ = compType {})
    : comp(std::forward<decltype(comp__)>(comp)) {}

    explicit
    myHeap(auto begin, auto end, compType && comp__ = compType {})
    : data(begin, end), comp(std::forward<decltype(comp__)>(comp)) {
        for (std::size_t i {(data.size() - 1) >> 1}; i != -1; --i) {
            shiftDown(i);
        }
    }

    auto size() const {
        return data.size();
    }

    auto empty() const -> bool {
        return data.empty();
    }

    auto insert(eleType && value) -> void {
        data.emplace_back(std::forward<delctype(value)>(value));

        shiftUp(data.size() - 1);
    }

    auto extract() -> eleType {
        if (empty()) {
            return eleType {};
        }

        eleType toRet {std::move(data.front())};

        data.front() = std::move(data.back());
        data.pop_back();

        shiftDown(0);

        return toRet;
    }
};