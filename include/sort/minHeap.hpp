#pragma once

#include <vector>
#include <stdexcept>

namespace dsa {
    template <typename ValueType>
    class minHeap {
    public:
        template <typename IteratorType>
        explicit minHeap(IteratorType begin, IteratorType end);
        explicit minHeap();

        auto size() const -> size_t;
        auto empty() const -> bool;

        void insert(ValueType value);
        auto extract() -> ValueType;

    private:
        void shiftUp(size_t index);
        void shiftDown(size_t index);

        std::vector<ValueType> data;
    };

    template <typename ValueType>
    template <typename IteratorType>
    minHeap<ValueType>::minHeap(IteratorType begin, IteratorType end)
    : data(begin, end) {
        for (size_t i {(data.size() - 2) >> 1}; i != -1; --i) {
            shiftDown(i);
        }
    }

    template <typename ValueType>
    minHeap<ValueType>::minHeap() {}

    template <typename ValueType>
    auto minHeap<ValueType>::size() const -> size_t {
        return data.size();
    }    

    template <typename ValueType>
    auto minHeap<ValueType>::empty() const -> bool {
        return data.empty();
    }

    template <typename ValueType>
    void minHeap<ValueType>::insert(ValueType value) {
        data.emplace_back(std::move(value));
    
        shiftUp(data.size() - 1);
    }

    template <typename ValueType>
    auto minHeap<ValueType>::extract() -> ValueType {
        if (data.empty()) {
            throw std::logic_error("no element in heap.");
        }
    
        ValueType tmp {std::move(data.front())};
    
        data.front() = std::move(data.back());
        data.pop_back();
    
        shiftDown(0);
    
        return tmp;
    }

    template <typename ValueType>
    void minHeap<ValueType>::shiftUp(size_t index) {
        ValueType tmp {std::move(data[index])};

        while (index != 0) {
            size_t fatherIndex {(index - 1) >> 1};

            if (tmp < data[fatherIndex]) {
                data[index] = std::move(data[fatherIndex]);

                index = fatherIndex;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }

    template <typename ValueType>
    void minHeap<ValueType>::shiftDown(size_t index) {
        ValueType tmp {std::move(data[index])};

        while ((index << 1) + 1 < data.size()) {
            size_t sonIndex {(index << 1) + 1};

            if (sonIndex + 1 < data.size()) {
                if (data[sonIndex + 1] < data[sonIndex]) {
                    ++sonIndex;
                }
            }

            if (data[sonIndex] < tmp) {
                data[index] = std::move(data[sonIndex]);

                index = sonIndex;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }
}