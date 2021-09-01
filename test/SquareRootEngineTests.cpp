#include <gtest/gtest.h>

#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TestUtility.hpp"
#include "utility.hpp"

struct SquareRootEngineTest : ::testing::Test {
  double mPrecision;
  int stepCount;
  int maxSpeed;
  float speed;
  float zero;
  float angle;
  SquareRootEngine engineSUT;

  SquareRootEngineTest()
      : mPrecision(0.0001),
        stepCount(1),
        maxSpeed(5),
        speed(1.f),
        zero(0.f),
        angle(0.f),
        engineSUT(stepCount, maxSpeed) {}
};

auto getSpeedDelta(auto speed_before, auto speed_after) { return speed_after - speed_before; }

TEST_F(SquareRootEngineTest,
       Given1StepCountAnd1UpdateAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  engineSUT.set_gear(Gear::Drive);

  engineSUT.update();

  EXPECT_NEAR(maxSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given1StepCountAndMultipleUpdatesAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  engineSUT.set_gear(Gear::Drive);

  update_many(engineSUT, 3);

  EXPECT_NEAR(maxSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given1StepCountAndReverseGearThenGetCurrentSpeedShouldReturnNegativeMaxSpeed) {
  engineSUT.set_gear(Gear::Reverse);

  engineSUT.update();

  EXPECT_NEAR(-maxSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    Given1StepCountAndMultipleUpdatesAndReverseGearThenGetCurrentSpeedShouldReturnNegativeMaxSpeed) {
  engineSUT.set_gear(Gear::Reverse);

  update_many(engineSUT, 3);

  EXPECT_NEAR(-maxSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenNeutralGearThenGetCurrentSpeedShouldReturn0) {
  engineSUT.set_gear(Gear::Neutral);

  engineSUT.update();

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given2StepCountAndDriveGearAndMaxSpeed1ThenGetCurrentSpeedShouldReturn07071) {
  stepCount = 2;
  maxSpeed = 1;
  float expectedSpeed = 0.7071f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);

  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given3StepCountAnd3UpdatesAndDriveGearThenGetCurrentSpeedShouldReturnMaxSpeed) {
  stepCount = 3;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);

  update_many(engineSUT, stepCount);

  EXPECT_NEAR(maxSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCountAndMaxSpeed3And1UpdateThenGetCurrentSpeedShouldReturn13416) {
  stepCount = 5;
  maxSpeed = 3.f;
  float expectedSpeed = 1.3416f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);

  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCountAndMaxSpeed3And2UpdatesThenGetCurrentSpeedShouldReturn18973) {
  stepCount = 5;
  maxSpeed = 3.f;
  float expectedSpeed = 1.8973f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);

  update_many(engineSUT, 2);

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenTankMovingForwardWhenGearSetToNeutralThenSpeedShouldDecrease) {
  stepCount = 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  engineSUT.update();
  auto speedBefore = engineSUT.get_current_speed();

  engineSUT.set_gear(Gear::Neutral);
  engineSUT.update();
  auto speedAfter = engineSUT.get_current_speed();

  EXPECT_TRUE(speedAfter < speedBefore);
}

TEST_F(SquareRootEngineTest, GivenTankMovingBackwardWhenGearSetToNeutralThenSpeedShouldIncrease) {
  stepCount = 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  engineSUT.update();
  auto speedBefore = engineSUT.get_current_speed();

  engineSUT.set_gear(Gear::Neutral);
  engineSUT.update();
  auto speedAfter = engineSUT.get_current_speed();

  EXPECT_TRUE(speedAfter > speedBefore);
}

TEST_F(SquareRootEngineTest,
       Given2StepCountAndMaxSpeedWhenGearSetToNeutralAnd2UpdatesThenGetCurrentSpeedShouldReturn0) {
  stepCount = 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  update_many(engineSUT, stepCount);

  engineSUT.set_gear(Gear::Neutral);
  update_many(engineSUT, stepCount);

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    Given2StepCountAndNegativeMaxSpeedWhenGearSetToNeutralAnd2UpdatesThenGetCurrentSpeedShouldReturn0) {
  stepCount = 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  update_many(engineSUT, stepCount);

  engineSUT.set_gear(Gear::Neutral);
  update_many(engineSUT, stepCount);

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount10WhenTankMovingForwardAndGearSetToNeutralThenGetCurrentSpeedShouldDecreaseBy1) {
  stepCount = 10;
  maxSpeed = 10;
  auto expectedSpeedDelta = -1.f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  update_many(engineSUT, stepCount);

  engineSUT.set_gear(Gear::Neutral);

  for (int i = 0; i < stepCount; i++) {
    auto speedBefore = engineSUT.get_current_speed();
    engineSUT.update();
    EXPECT_NEAR(expectedSpeedDelta, getSpeedDelta(speedBefore, engineSUT.get_current_speed()),
                mPrecision);
  }
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount10WhenTankMovingBackwardAndGearSetToNeutralThenSpeedShouldIncreaseBy1) {
  stepCount = 10;
  maxSpeed = 10;
  auto expectedSpeedDelta = 1.f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  update_many(engineSUT, stepCount);

  engineSUT.set_gear(Gear::Neutral);

  for (int i = 0; i < stepCount; i++) {
    auto speedBefore = engineSUT.get_current_speed();
    engineSUT.update();
    EXPECT_NEAR(expectedSpeedDelta, getSpeedDelta(speedBefore, engineSUT.get_current_speed()),
                mPrecision);
  }
}

TEST_F(
    SquareRootEngineTest,
    GivenMaxSpeed10AndStepCount5WhenTankMovingBackwardAndGearSetToNeutralThenSpeedShouldDecreaseBy2) {
  stepCount = 5;
  maxSpeed = 10;
  auto expectedSpeedDelta = -2.f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  update_many(engineSUT, stepCount);

  engineSUT.set_gear(Gear::Neutral);

  for (int i = 0; i < stepCount; i++) {
    auto speedBefore = engineSUT.get_current_speed();
    engineSUT.update();
    EXPECT_NEAR(expectedSpeedDelta, getSpeedDelta(speedBefore, engineSUT.get_current_speed()),
                mPrecision);
  }
}

TEST_F(
    SquareRootEngineTest,
    GivenDriveGearMaxSpeed3AndStepCount5And3UpdatesWhenGearSetToNeutralAnd4UpdatesThenGetCurrentSpeedShouldReturn0) {
  stepCount = 5;
  maxSpeed = 3;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  update_many(engineSUT, 3);

  engineSUT.set_gear(Gear::Neutral);
  update_many(engineSUT, 4);

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenReverseGearMaxSpeed3AndStepCount5And3UpdatesWhenGearSetToNeutralAnd4UpdatesThenGetCurrentSpeedShouldReturn0) {
  stepCount = 5;
  maxSpeed = 3;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  update_many(engineSUT, 3);

  engineSUT.set_gear(Gear::Neutral);
  update_many(engineSUT, 4);

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenTankMovingForwardAndMaxSpeed10AndStepCount10WhenGearSetToReverseThenSpeedShouldDecreaseBy3DownTo0) {
  stepCount = 10;
  maxSpeed = 10;
  auto expectedSpeedDelta = -3.f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  update_many(engineSUT, stepCount);
  engineSUT.set_gear(Gear::Reverse);
  for (int i = 0; i < 3; i++) {
    auto speedBefore = engineSUT.get_current_speed();
    engineSUT.update();
    EXPECT_NEAR(expectedSpeedDelta, getSpeedDelta(speedBefore, engineSUT.get_current_speed()),
                mPrecision);
  }
  engineSUT.update();
  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(
    SquareRootEngineTest,
    GivenTankMovingBackwardAndMaxSpeed10AndStepCount10WhenGearSetToDriveThenSpeedShouldIncreaseBy3UpTo0) {
  stepCount = 10;
  maxSpeed = 10;
  auto expectedSpeedDelta = 3.f;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  update_many(engineSUT, stepCount);
  engineSUT.set_gear(Gear::Drive);
  for (int i = 0; i < 3; i++) {
    auto speedBefore = engineSUT.get_current_speed();
    engineSUT.update();
    EXPECT_NEAR(expectedSpeedDelta, getSpeedDelta(speedBefore, engineSUT.get_current_speed()),
                mPrecision);
  }
  engineSUT.update();
  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenCurrentSpeed0ThenGetPositionDeltaShouldReturnEmptyVector) {
  angle = 0.5f;
  expect_vec2f_eq({0.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest,
       GivenSameAngleAndSpeedWhenMultipleUpdatesThenGetPositionDeltaShouldReturnSameVector) {
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  sf::Vector2f expectedVector = {0.f, -5.f};
  engineSUT.set_gear(Gear::Drive);

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));
}

TEST_F(SquareRootEngineTest, Given90AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveRight) {
  angle = pi / 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  engineSUT.update();
  expect_vec2f_eq({5.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given180AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveDown) {
  angle = pi;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  engineSUT.update();
  expect_vec2f_eq({0.f, 5.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given180AngleAndReverseGearThenGetPositionDeltaShouldReturnMoveUp) {
  angle = pi;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  engineSUT.update();
  expect_vec2f_eq({0.f, -5.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given270AngleAndDriveGearThenGetPositionDeltaShouldReturnMoveLeft) {
  angle = pi + pi / 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);
  engineSUT.update();
  expect_vec2f_eq({-5.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given270AngleAndReverseGearThenGetPositionDeltaShouldReturnMoveRight) {
  angle = pi + pi / 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Reverse);
  engineSUT.update();
  expect_vec2f_eq({5.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, GivenDynamicSpeedThenGetPositionDeltaShouldOnlyReturnDelta) {
  stepCount = 2;
  maxSpeed = 1;
  angle = pi / 2;
  SquareRootEngine engineSUT(stepCount, maxSpeed);
  engineSUT.set_gear(Gear::Drive);

  engineSUT.update();
  expect_vec2f_eq({0.7071f, 0.f}, engineSUT.get_position_delta(angle));

  engineSUT.update();
  expect_vec2f_eq({1.f, 0.f}, engineSUT.get_position_delta(angle));
}
