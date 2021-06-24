#include <gtest/gtest.h>
#include <string>
#include <array>
#include <algorithm>
#include "Random.hpp"


TEST(OneOfTest, OneIntShouldBeChosen) {
    EXPECT_EQ(42, one_of(42));
}

TEST(OneOfTest, TwoInts_RunTenTimes_ShouldChooseBothAtLeastThreeTimes) {
    std::array<int, 10> ints;
    std::ranges::generate(ints, []{ return one_of(1, 2);});
    EXPECT_GE(std::ranges::count(ints, 1), 3);
    EXPECT_GE(std::ranges::count(ints, 2), 3);
}
