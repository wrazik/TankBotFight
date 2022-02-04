#include <gtest/gtest.h>

#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TestUtility.hpp"
#include "utility.hpp"

struct GetAngleTestParam {
  std::string mTestName{};
  sf::Vector2f mVector{};
  float mExpectedDegrees{};

  friend std::ostream& operator<<(std::ostream& os, const GetAngleTestParam& p) {
    os << p.mTestName;
    return os;
  }
};

class GetAngleTests : public ::testing::TestWithParam<GetAngleTestParam> {};

TEST_P(GetAngleTests, TestingGetAngleWithManyParameters) {
  auto param = GetParam();

  auto actual_degrees = get_angle(param.mVector);

  EXPECT_NEAR(param.mExpectedDegrees, actual_degrees, PRECISION);
}

INSTANTIATE_TEST_CASE_P(
    GetAngleTestInstantiation, GetAngleTests,
    ::testing::Values(
        GetAngleTestParam{"Given: {1.f, -1.f} vector then return 45 degrees", {1.f, -1.f}, 45.f},
        GetAngleTestParam{"Given: {0.f, 0.f} vector then return 0 degrees", {0.f, 0.f}, 0.f},
        GetAngleTestParam{"Given: {5.f, 0.f} vector then return 90 degrees", {5.f, 0.f}, 90.f},
        GetAngleTestParam{"Given: {0.f, 3.f} vector then return 180 degrees", {0.f, 3.f}, 180.f},
        GetAngleTestParam{"Given: {1.f, 1.f} vector then return 135 degrees", {1.f, 1.f}, 135.f},
        GetAngleTestParam{"Given: {0.f, -1.f} vector then return 0 degrees", {0.f, -1.f}, 0.f},
        GetAngleTestParam{"Given: {-1.f, 1.f} vector then return 225 degrees", {-1.f, 1.f}, 225.f},
        GetAngleTestParam{"Given: {-1.f, 0.f} vector then return 270 degrees", {-1.f, 0.f}, 270.f},
        GetAngleTestParam{
            "Given: {-1.f, -1.f} vector then return 315 degrees", {-1.f, -1.f}, 315.f},
        GetAngleTestParam{
            "Given: {-sqrt(3.f), -1.f} vector then return 300 degrees", {-sqrt(3.f), -1.f}, 300.f},
        GetAngleTestParam{"Given: {-1.f, -sqrt(3.f)} vector then return 330 degrees",
                          {-1.f, -sqrt(3.f)},
                          330.f}));

TEST(GetAngleTest, GetAngleShouldComplementGetPositionDelta) {
  SquareRootEngine engine{SquareRootEngineConfig{.mStepCount = 1, .mMaxSpeed = 2.f}};
  float expected_angle_radians = PI / 4;
  engine.set_gear(Gear::Drive);
  engine.update();

  auto actual_angle_degrees = get_angle(engine.get_position_delta(expected_angle_radians));

  EXPECT_NEAR(actual_angle_degrees, to_degrees(expected_angle_radians), PRECISION);
}

TEST(FindAllTest, GivenNoElementsFoundInRange_WhenFindAllCalled_ThenReturnEmptyVector) {
  std::vector<int> collection{1, 3, 5};
  const auto& iters =
      find_all(collection.cbegin(), collection.cend(), [](const int val) { return val % 2 == 0; });
  const auto& elems = dereference_vec(iters);
  expect_vec_eq(elems, std::vector<int>{});
}

TEST(FindAllTest, GivenOneElementFoundInRange_WhenFindAllCalled_ThenReturnOneIterator) {
  std::vector<int> collection{1, 3, 5};
  const auto& iters =
      find_all(collection.cbegin(), collection.cend(), [](const int val) { return val == 5; });
  const auto& elems = dereference_vec(iters);
  expect_vec_eq(elems, std::vector<int>{5});
}

TEST(FindAllTest, GivenMultipleElementsFoundInRange_WhenFindAllCalled_ThenReturnAllIterators) {
  std::vector<int> collection{1, 2, 3, 4, 5, 6};
  const auto& iters =
      find_all(collection.cbegin(), collection.cend(), [](const int val) { return val % 2 == 0; });
  const auto& elems = dereference_vec(iters);
  expect_vec_eq(elems, std::vector<int>{2, 4, 6});
}
