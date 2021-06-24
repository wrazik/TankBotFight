#include "Random.hpp"

#include <random>

int random_range(const int begin, const int end) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<> rand(begin, end);
  return rand(rng);
}
