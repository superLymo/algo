#pragma once

#include <chrono>
namespace dsa {
    auto timeFigure(auto && func) -> double {
        auto time1 {std::chrono::system_clock::now()};

        func();

        auto time2 {std::chrono::system_clock::now()};

        return std::chrono::duration<double>(time2 - time1).count();
    }
}