#pragma once

#include <random>

namespace Utils {
  inline int RandInt(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
  }
}
