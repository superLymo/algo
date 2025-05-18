#include <print>
#include <random>

auto main() -> int {
    std::random_device seedGen;
    std::mt19937 numGen(seedGen());

    std::uniform_int_distribution<> rangeGen(0, 100);

    for (std::size_t i {}; i != 10; ++i) {
        std::println("{}", rangeGen(numGen));
    }
    
    return 0;
}