#pragma once
#include <array>

[[nodiscard]] int random_range(int begin, int end);

template <typename T, typename... Args>
T one_of(T first, Args... rest) {
  std::array<T, sizeof...(rest) + 1> array = {first, rest...};

  return array.at(random_range(0, sizeof...(rest)));
}
