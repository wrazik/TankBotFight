#include <gtest/gtest.h>

#include <array>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/generate.hpp>

#include "Random.hpp"

TEST(OneOfTest, OneIntShouldBeChosen) { EXPECT_EQ(42, one_of(42)); }

TEST(OneOfTest, TwoInts_RunMultipleTimes_ShouldChooseBothAtLeastThreeTimes) {
  std::array<int, 12> ints;
  ranges::generate(ints, [] { return one_of(1, 2); });
  EXPECT_GE(ranges::count(ints, 1), 3);
  EXPECT_GE(ranges::count(ints, 2), 3);
}
