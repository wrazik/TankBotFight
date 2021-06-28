#pragma once
#include <exception>
#include <vector>

template <typename T>
void fill_vec(std::vector<std::vector<T>>& vec, const int start_x, const int start_y,
              const int end_x, const int end_y, const T value) {
  if (end_x < start_x || end_y < start_y) {
    throw std::runtime_error("Invalid range for filling!");
  }

  for (int i = start_x; i <= end_x; ++i) {
    for (int j = start_y; j <= end_y; ++j) {
      vec[i][j] = value;
    }
  }
}
