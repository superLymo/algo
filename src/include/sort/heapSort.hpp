#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace dsa {
    template <typename ValueType>
    class maxHeap {
    public:
        maxHeap(maxHeap &&) = delete;
        maxHeap(maxHeap const &) = delete;

        template <typename IteratorType>
        explicit maxHeap(IteratorType begin, IteratorType end);
        explicit maxHeap();

        auto size() const -> size_t;
        auto empty() const -> bool;

        void insert(ValueType value);
        auto extract() -> ValueType;

        auto getData() const -> std::vector<ValueType>;

    private:
        void shiftUp(size_t index);
        void shiftDown(size_t index);

        std::vector<ValueType> data;
    };

    template <typename ValueType>
    template <typename IteratorType>
    maxHeap<ValueType>::maxHeap(IteratorType begin, IteratorType end) 
    : data(begin, end) {
        for (size_t i {(data.size() - 2) >> 1}; i != -1; --i) {
            shiftDown(i);
        }
    }

    template <typename ValueType>
    maxHeap<ValueType>::maxHeap() {}

    template <typename ValueType>
    auto maxHeap<ValueType>::size() const -> size_t {
        return data.size();
    }

    template <typename ValueType>
    auto maxHeap<ValueType>::empty() const -> bool {
        return data.empty();
    }

    template <typename ValueType>
    void maxHeap<ValueType>::insert(ValueType value) {
        data.emplace_back(std::move(value));

        shiftUp(data.size() - 1);
    }

    template <typename ValueType>
    auto maxHeap<ValueType>::extract() -> ValueType {
        if (empty()) {
            throw std::logic_error("no element in heap.");
        }

        ValueType toReturn {std::move(data.front())};
        data.front() = std::move(data.back());
        data.pop_back();

        shiftDown(0);

        return toReturn;
    }

    template <typename ValueType>
    auto maxHeap<ValueType>::getData() const -> std::vector<ValueType> {
        return data;
    }

    template <typename ValueType>
    void maxHeap<ValueType>::shiftUp(size_t index) {
        ValueType tmp {std::move(data[index])};

        while (index != 0) {
            size_t fatherIndex {(index - 1) >> 1};

            if (data[fatherIndex] < tmp) {
                data[index] = std::move(data[fatherIndex]);

                index = fatherIndex;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }

    template <typename ValueType>
    void maxHeap<ValueType>::shiftDown(size_t index) {
        ValueType tmp {std::move(data[index])};

        while ((index * 2 + 1) < data.size()) {
            size_t sonIndex {index * 2 + 1};

            if (sonIndex + 1 < data.size()) {
                if (data[sonIndex] < data[sonIndex + 1]) {
                    ++sonIndex;
                }
            }

            if (tmp < data[sonIndex]) {
                data[index] = std::move(data[sonIndex]);

                index = sonIndex;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }
}