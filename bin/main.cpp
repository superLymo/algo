#include <cstddef>
#include <print>
#include <thread>
#include <vector>

template <std::size_t T>
struct getSum {
    static constexpr auto value = T + getSum<T - 1>::value;
};

template <>
struct getSum<0> {
    static constexpr auto value = 0;
};

auto main() -> int {
    int constexpr num {10};

    std::println("{0:s^+#20o}", 123, 12);
    std::println("{0:f>+#25.4f}", 3.123231323232323);

    return 0;
}

// 位置：填充 对齐 正负显示 前缀显示 前填充0 宽度 精度 类型