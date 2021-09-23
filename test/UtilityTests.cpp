#include <gtest/gtest.h>

#include "TestUtility.hpp"
#include "utility.hpp"
#include "Size.hpp"
#include "SquareRootEngine.hpp"

struct GetAngleTestParam {
  std::string testName{};
  sf::Vector2f vector{};
  float expectedDegrees{};

  friend std::ostream& operator<<(std::ostream& os, const GetAngleTestParam& p) {
      os << p.testName;
      return os;
  }
};

class GetAngleTests : public ::testing::TestWithParam<GetAngleTestParam> {};

TEST_P(GetAngleTests, TestingGetAngleWithManyParameters) {
  auto param = GetParam();

  auto actualDegrees = get_angle(param.vector);

  EXPECT_NEAR(param.expectedDegrees, actualDegrees, precision);
}

INSTANTIATE_TEST_CASE_P(
    GetAngleTestInstantiation, GetAngleTests,
    ::testing::Values(GetAngleTestParam{
        "Given: {1.f, -1.f} vector then return 45 degrees", {1.f, -1.f}, 45.f},
        GetAngleTestParam{
        "Given: {0.f, 0.f} vector then return 0 degrees", {0.f, 0.f}, 0.f},  
        GetAngleTestParam{
        "Given: {5.f, 0.f} vector then return 90 degrees", {5.f, 0.f}, 90.f}, 
        GetAngleTestParam{
        "Given: {0.f, 3.f} vector then return 180 degrees", {0.f, 3.f}, 180.f},
        GetAngleTestParam{
        "Given: {1.f, 1.f} vector then return 135 degrees", {1.f, 1.f}, 135.f},
        GetAngleTestParam{
        "Given: {0.f, -1.f} vector then return 0 degrees", {0.f, -1.f}, 0.f},
        GetAngleTestParam{
        "Given: {-1.f, 1.f} vector then return 225 degrees", {-1.f, 1.f}, 225.f},
        GetAngleTestParam{
        "Given: {-1.f, 0.f} vector then return 270 degrees", {-1.f, 0.f}, 270.f},
        GetAngleTestParam{
        "Given: {-1.f, -1.f} vector then return 315 degrees", {-1.f, -1.f}, 315.f},
        GetAngleTestParam{
        "Given: {-sqrt(3.f), -1.f} vector then return 300 degrees", {-sqrt(3.f), -1.f}, 300.f},
         GetAngleTestParam{
        "Given: {-1.f, -sqrt(3.f)} vector then return 330 degrees", {-1.f, -sqrt(3.f)}, 330.f}));


TEST(GetAngleTest, GetAngleShouldComplementGetPositionDelta) {
  SquareRootEngine engine(1, 2);
  float expectedAngleRadians = pi / 4;
  engine.set_gear(Gear::Drive);
  engine.update();
 
  auto actualAngleDegrees = get_angle(engine.get_position_delta(expectedAngleRadians));

  EXPECT_NEAR(actualAngleDegrees, to_degrees(expectedAngleRadians), precision);
}
