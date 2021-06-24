#pragma once
#include <vector>

int random_range(const int begin, const int end);

template <typename T, typename... Args>
T one_of(T first, Args... rest) {
  T array[sizeof...(rest) + 1] = {first, rest...};

  return array[random_range(0, sizeof...(rest))];
}
