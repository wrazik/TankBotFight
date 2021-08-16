#include <gtest/gtest.h>

#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TestUtility.hpp"

struct SquareRootEngineTest : ::testing::Test {
  double mPrecision;
  int stepCount;
  float speed;
  float zero;
  float angle;
  void SetUp() override {
    mPrecision = 0.0001;
    stepCount = 1;
    speed = 1.f;
    zero = 0.f;
    angle = 0.f;
  }
};

TEST_F(SquareRootEngineTest, Given1StepCountWhenSetSpeed1ThenGetCurrentSpeedShouldReturn1) {
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();

  EXPECT_NEAR(speed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, WhenSetSpeed0ThenGetCurrentSpeedShouldReturn0) {
  speed = 0.f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();

  EXPECT_NEAR(speed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, GivenMovingTankWhenSetSpeed0ThenGetCurrentSpeedShouldReturn0) {
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);
  engineSUT.update();
  engineSUT.set_speed(zero);

  engineSUT.update();

  EXPECT_NEAR(zero, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, Given2StepCountWhenSetSpeed1ThenGetCurrentSpeedShouldReturn07071) {
  stepCount = 2;
  float expectedSpeed = 0.7071f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given2StepCountAnd2UpdatesWhenSetSpeed1ThenGetCurrentSpeedShouldReturn1) {
  stepCount = 2;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();
  engineSUT.update();

  EXPECT_NEAR(speed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, Given5StepCountWhenSetSpeed3ThenGetCurrentSpeedShouldReturn13416) {
  stepCount = 5;
  speed = 3.f;
  float expectedSpeed = 1.3416f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCount2UpdatesWhenSetSpeed3ThenGetCurrentSpeedShouldReturn18973) {
  stepCount = 5;
  speed = 3.f;
  float expectedSpeed = 1.8973f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();
  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       Given5StepCount4UpdatesWhenSetSpeed3ThenGetCurrentSpeedShouldReturn26832) {
  stepCount = 5;
  speed = 3.f;
  float expectedSpeed = 2.6832f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();
  engineSUT.update();
  engineSUT.update();
  engineSUT.update();

  EXPECT_NEAR(expectedSpeed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest,
       GivenNStepCountAndNUpdatesWhenSetSpeedThenGetCurrentSpeedShouldReturnSetSpeed) {
  stepCount = 30;
  speed = 15.5f;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  for (int i = 0; i < stepCount; ++i) {
    engineSUT.update();
  }

  EXPECT_NEAR(speed, engineSUT.get_current_speed(), mPrecision);
}

TEST_F(SquareRootEngineTest, WhenSetSpeed0ThenGetPositionDeltaShouldReturnEmptyVector) {
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(zero);

  engineSUT.update();

  expect_vec2f_eq({0.f, 0.f}, engineSUT.get_position_delta(zero));
}

TEST_F(SquareRootEngineTest,
       GivenMovingTankWhenSetSpeed0ThenGetPositionDeltaShouldReturnEmptyVector) {
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);
  engineSUT.update();
  engineSUT.set_speed(zero);

  engineSUT.update();

  expect_vec2f_eq({0.f, 0.f}, engineSUT.get_position_delta(zero));
}

TEST_F(SquareRootEngineTest,
       GivenSameAngleAndSpeedWhenMultipleUpdatesThenGetPositionDeltaShouldReturnSameVector) {
  SquareRootEngine engineSUT(stepCount);
  sf::Vector2f expectedVector = {0.f, -1.f};
  engineSUT.set_speed(speed);

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));

  engineSUT.update();
  expect_vec2f_eq(expectedVector, engineSUT.get_position_delta(zero));
}

TEST_F(SquareRootEngineTest, Given90AngleThenGetPositionDeltaShouldReturnMoveRight) {
  angle = pi / 2;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);
  engineSUT.update();
  expect_vec2f_eq({1.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given180AngleThenGetPositionDeltaShouldReturnMoveDown) {
  angle = pi;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);
  engineSUT.update();
  expect_vec2f_eq({0.f, 1.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, Given270AngleThenGetPositionDeltaShouldReturnMoveLeft) {
  angle = pi + pi / 2;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);
  engineSUT.update();
  expect_vec2f_eq({-1.f, 0.f}, engineSUT.get_position_delta(angle));
}

TEST_F(SquareRootEngineTest, GivenSubsequentUpdatesThenGetPositionDeltaShouldOnlyReturnDelta) {
  stepCount = 2;
  angle = pi / 2;
  SquareRootEngine engineSUT(stepCount);
  engineSUT.set_speed(speed);

  engineSUT.update();
  expect_vec2f_eq({0.7071f, 0.f}, engineSUT.get_position_delta(angle));

  engineSUT.update();
  expect_vec2f_eq({1.f, 0.f}, engineSUT.get_position_delta(angle));
}

