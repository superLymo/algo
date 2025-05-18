#pragma once

#include <Windows.h>
#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

inline
std::string exec(const char *cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("_popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

inline
void test() {
    std::string output = exec("fd java.exe D:/");
    std::cout << "Output: " << output << std::endl;
}