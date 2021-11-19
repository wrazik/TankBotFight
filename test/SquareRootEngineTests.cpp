#include <gtest/gtest.h>

#include <range/v3/view/iota.hpp>

#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TestUtility.hpp"
#include "utility.hpp"

constexpr auto get_speed_delta(auto speed_before, auto speed_after) {
  return speed_after - speed_before;
}

struct SquareRootEngineTest : ::testing::Test {
  double mPrecision{0.0001};
  int mStepCount{1};
  float mMaxSpeed{5};
  float mSpeed{1.f};
  float mZero{0.f};
  float mAngle{0.f};
  SquareRootEngine mEngineSUT{mStepCount, mMaxSpeed};

  void assert_speed_delta(const auto expected_speed_delta, const int count) {
    for (int i : ranges::iota_view(0, count)) {
      const auto speed_before = mEngineSUT.get_current_speed();
      mEngineSUT.update();
      EXPECT_NEAR(expected_speed_delta,
                  get_speed_delta(speed_before, mEngineSUT.get_current_speed()), mPrecision);
    }
  }
};

TEST_F(SquareRootEngineTest,
       Given1StepCountAnd1UpdateAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  EXPECT_NEAR(mMaxSpeed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given1StepCountAndMultipleUpdatesAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  mEngineSUT.set_gear(Gear::Drive);

  update_many(mEngineSUT, 3);

  EXPECT_NEAR(mMaxSpeed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given1StepCountAndReverseGearThenGetCurrentSpeedShouldReturnNegativeMaxSpeed) {
  mEngineSUT.set_gear(Gear::Reverse);

  mEngineSUT.update();

  EXPECT_NEAR(-mMaxSpeed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    Given1StepCountAndMultipleUpdatesAndReverseGearThenGetCurrentSpeedShouldReturnNegativeMaxSpeed) {
  mEngineSUT.set_gear(Gear::Reverse);

  update_many(mEngineSUT, 3);

  EXPECT_NEAR(-mMaxSpeed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenNeutralGearThenGetCurrentSpeedShouldReturn0) {
  mEngineSUT.set_gear(Gear::Neutral);

  mEngineSUT.update();

  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given2StepCountAndDriveGearAndMaxSpeed1ThenGetCurrentSpeedShouldReturn07071) {
  mStepCount = 2;
  mMaxSpeed = 1;
  const float expected_speed = 0.7071f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  EXPECT_NEAR(expected_speed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given3StepCountAnd3UpdatesAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  mStepCount = 3;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);

  update_many(mEngineSUT, mStepCount);

  EXPECT_NEAR(mMaxSpeed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCountAndMaxSpeed3And1UpdateThenGetCurrentSpeedShouldReturn13416) {
  mStepCount = 5;
  mMaxSpeed = 3.f;
  const float expected_speed = 1.3416f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  EXPECT_NEAR(expected_speed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCountAndMaxSpeed3And2UpdatesThenGetCurrentSpeedShouldReturn18973) {
  mStepCount = 5;
  mMaxSpeed = 3.f;
  const float expected_speed = 1.8973f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);

  update_many(mEngineSUT, 2);

  EXPECT_NEAR(expected_speed, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenTankMovingForwardWhenGearSetToNeutralThenSpeedShouldDecrease) {
  mStepCount = 2;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  mEngineSUT.update();
  const auto speed_before = mEngineSUT.get_current_speed();

  mEngineSUT.set_gear(Gear::Neutral);
  mEngineSUT.update();
  const auto speed_after = mEngineSUT.get_current_speed();

  EXPECT_TRUE(speed_after < speed_before);
}

TEST_F(SquareRootEngineTest, GivenTankMovingBackwardWhenGearSetToNeutralThenSpeedShouldIncrease) {
  mStepCount = 2;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Reverse);
  mEngineSUT.update();
  const auto speed_before = mEngineSUT.get_current_speed();

  mEngineSUT.set_gear(Gear::Neutral);
  mEngineSUT.update();
  const auto speed_after = mEngineSUT.get_current_speed();

  EXPECT_TRUE(speed_after > speed_before);
}

TEST_F(SquareRootEngineTest,
       Given2StepCountAndMaxSpeedWhenGearSetToNeutralAnd2UpdatesThenGetCurrentSpeedShouldReturn0) {
  mStepCount = 2;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  update_many(mEngineSUT, mStepCount);

  mEngineSUT.set_gear(Gear::Neutral);
  update_many(mEngineSUT, mStepCount);

  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    Given2StepCountAndNegativeMaxSpeedWhenGearSetToNeutralAnd2UpdatesThenGetCurrentSpeedShouldReturn0) {
  mStepCount = 2;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Reverse);
  update_many(mEngineSUT, mStepCount);

  mEngineSUT.set_gear(Gear::Neutral);
  update_many(mEngineSUT, mStepCount);

  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount10WhenTankMovingForwardAndGearSetToNeutralThenGetCurrentSpeedShouldDecreaseBy1) {
  mStepCount = 10;
  mMaxSpeed = 10;
  const auto expected_speed_delta = -1.f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  update_many(mEngineSUT, mStepCount);

  mEngineSUT.set_gear(Gear::Neutral);

  assert_speed_delta(expected_speed_delta, mStepCount);
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount10WhenTankMovingBackwardAndGearSetToNeutralThenSpeedShouldIncreaseBy1) {
  mStepCount = 10;
  mMaxSpeed = 10;
  const auto expected_speed_delta = 1.f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Reverse);
  update_many(mEngineSUT, mStepCount);

  mEngineSUT.set_gear(Gear::Neutral);

  assert_speed_delta(expected_speed_delta, mStepCount);
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount5WhenTankMovingBackwardAndGearSetToNeutralThenSpeedShouldDecreaseBy2) {
  mStepCount = 5;
  mMaxSpeed = 10;
  const auto expected_speed_delta = -2.f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  update_many(mEngineSUT, mStepCount);

  mEngineSUT.set_gear(Gear::Neutral);

  assert_speed_delta(expected_speed_delta, mStepCount);
}

TEST_F(
    SquareRootEngineTest,
    GivenDriveGearMaxSpeed3AndStepCount5And3UpdatesWhenGearSetToNeutralAnd4UpdatesThenGetCurrentSpeedShouldReturn0) {
  mStepCount = 5;
  mMaxSpeed = 3;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  update_many(mEngineSUT, 3);

  mEngineSUT.set_gear(Gear::Neutral);
  update_many(mEngineSUT, 4);

  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenReverseGearMaxSpeed3AndStepCount5And3UpdatesWhenGearSetToNeutralAnd4UpdatesThenGetCurrentSpeedShouldReturn0) {
  mStepCount = 5;
  mMaxSpeed = 3;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Reverse);
  update_many(mEngineSUT, 3);

  mEngineSUT.set_gear(Gear::Neutral);
  update_many(mEngineSUT, 4);

  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenTankMovingForwardAndMaxSpeed10AndStepCount10WhenGearSetToReverseThenSpeedShouldDecreaseBy3DownTo0) {
  mStepCount = 10;
  mMaxSpeed = 10;
  const auto expected_speed_delta = -3.f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);
  update_many(mEngineSUT, mStepCount);
  mEngineSUT.set_gear(Gear::Reverse);

  assert_speed_delta(expected_speed_delta, 3);

  mEngineSUT.update();
  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenTankMovingBackwardAndMaxSpeed10AndStepCount10WhenGearSetToDriveThenSpeedShouldIncreaseBy3UpTo0) {
  mStepCount = 10;
  mMaxSpeed = 10;
  const auto expected_speed_delta = 3.f;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Reverse);
  update_many(mEngineSUT, mStepCount);
  mEngineSUT.set_gear(Gear::Drive);

  assert_speed_delta(expected_speed_delta, 3);

  mEngineSUT.update();
  EXPECT_NEAR(mZero, mEngineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenCurrentSpeed0ThenGetPositionDeltaShouldReturnEmptyVector) {
  mAngle = 0.5f;
  expect_vec2f_eq({0.f, 0.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest,
       GivenSameAngleAndSpeedWhenMultipleUpdatesThenGetPositionDeltaShouldReturnSameVector) {
  const sf::Vector2f expected_vector = {0.f, -5.f};
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();
  expect_vec2f_eq(expected_vector, mEngineSUT.get_position_delta(mZero));

  mEngineSUT.update();
  expect_vec2f_eq(expected_vector, mEngineSUT.get_position_delta(mZero));

  mEngineSUT.update();
  expect_vec2f_eq(expected_vector, mEngineSUT.get_position_delta(mZero));
}

TEST_F(SquareRootEngineTest, Given90AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveRight) {
  mAngle = PI / 2;
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  expect_vec2f_eq({5.f, 0.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest, Given180AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveDown) {
  mAngle = PI;
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  expect_vec2f_eq({0.f, 5.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest, Given180AngleAndReverseGearThenGetPositionDeltaShouldReturnMoveUp) {
  mAngle = PI;
  mEngineSUT.set_gear(Gear::Reverse);

  mEngineSUT.update();

  expect_vec2f_eq({0.f, -5.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest, Given270AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveLeft) {
  mAngle = PI + PI / 2;
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();

  expect_vec2f_eq({-5.f, 0.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest, Given270AngleAndReverseGearThenGetPositionDeltaShouldReturnMoveRight) {
  mAngle = PI + PI / 2;
  mEngineSUT.set_gear(Gear::Reverse);

  mEngineSUT.update();

  expect_vec2f_eq({5.f, 0.f}, mEngineSUT.get_position_delta(mAngle));
}

TEST_F(SquareRootEngineTest, GivenDynamicSpeedThenGetPositionDeltaShouldOnlyReturnDelta) {
  mStepCount = 2;
  mMaxSpeed = 1;
  mAngle = PI / 2;
  mEngineSUT = SquareRootEngine(mStepCount, mMaxSpeed);
  mEngineSUT.set_gear(Gear::Drive);

  mEngineSUT.update();
  expect_vec2f_eq({0.7071f, 0.f}, mEngineSUT.get_position_delta(mAngle));

  mEngineSUT.update();
  expect_vec2f_eq({1.f, 0.f}, mEngineSUT.get_position_delta(mAngle));
}
