#include <algorithm>
#include <atomic>
#include <array>
#include <cstddef>
#include <optional>
#include <iostream>
#include <thread>
#include <vector>


template <typename T, size_t SIZE>
class LockFreeQueue {
public:
    LockFreeQueue() : head_(0), tail_(0) {}

    // 入队操作
    bool enqueue(const T& value) {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t current_head = head_.load(std::memory_order_relaxed);

        // 检查队列是否已满
        if (((current_tail + 1) % SIZE) == current_head) {
            return false; // 队列已满
        }

        // 存储值到队列
        data_[current_tail] = value;

        // 更新尾索引，使用释放语义以确保之前的写入操作对其他线程可见
        tail_.store((current_tail + 1) % SIZE, std::memory_order_release);
        return true;
    }

    // 出队操作
    std::optional<T> dequeue() {
        size_t current_head = head_.load(std::memory_order_relaxed);
        size_t current_tail = tail_.load(std::memory_order_relaxed);

        // 检查队列是否为空
        if (current_head == current_tail) {
            return std::nullopt; // 队列为空
        }

        // 获取值
        T value = data_[current_head];

        // 更新头索引，使用释放语义以确保之前的写入操作对其他线程可见
        head_.store((current_head + 1) % SIZE, std::memory_order_release);
        return value;
    }

    // 检查队列是否为空
    bool is_empty() const {
        size_t current_head = head_.load(std::memory_order_relaxed);
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        return current_head == current_tail;
    }

    // 检查队列是否已满
    bool is_full() const {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t current_head = head_.load(std::memory_order_relaxed);
        return ((current_tail + 1) % SIZE) == current_head;
    }

private:
    std::array<T, SIZE> data_;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
};