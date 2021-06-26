#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>

#include "Random.hpp"

TEST(OneOfTest, OneIntShouldBeChosen) { EXPECT_EQ(42, one_of(42)); }

TEST(OneOfTest, TwoInts_RunMultipleTimes_ShouldChooseBothAtLeastThreeTimes) {
  std::array<int, 12> ints;
  std::ranges::generate(ints, [] { return one_of(1, 2); });
  EXPECT_GE(std::ranges::count(ints, 1), 3);
  EXPECT_GE(std::ranges::count(ints, 2), 3);
}
