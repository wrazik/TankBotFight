#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <utility>

#include "SquareRootEngine.hpp"
#include "Tank/Tank.hpp"
#include "Sound.hpp"
#include "TestUtility.hpp"
#include "TracesHandler.hpp"
#include "gmock/gmock.h"
#include "utility.hpp"

struct EngineMock : Engine {
  MOCK_METHOD(void, set_gear, (Gear), (override));
  MOCK_METHOD(float, get_current_speed, (), (const, override));
  MOCK_METHOD(sf::Vector2f, get_position_delta, (float), (override));
  MOCK_METHOD(std::unique_ptr<Engine>, copy, (), (const, override));
  MOCK_METHOD(void, update, (), (override));
};

struct TankTestData {
  std::unique_ptr<sf::Texture> mBody{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mTower{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mShot{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mTracks{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mMissile{create_dummy_texture()};
  Sound emptySound;
  TankTextures mTextures{.mBody = *mBody,
                         .mTower = *mTower,
                         .mShot = *mShot,
                         .mTracks = *mTracks,
                         .mMissile = *mMissile};
  std::unique_ptr<testing::NiceMock<EngineMock>> mEngine{
      std::make_unique<testing::NiceMock<EngineMock>>()};
  std::shared_ptr<testing::NiceMock<EngineMock>> mEngineNiceMock{
      std::shared_ptr<testing::NiceMock<EngineMock>>{}, mEngine.get()};
  std::chrono::milliseconds shot_cooldown = std::chrono::milliseconds{500};
  unsigned int health = 100;

  Tank create_tank(std::unique_ptr<testing::NiceMock<EngineMock>>&& engine) {
    return {0, 0, mTextures, std::move(engine),
            emptySound,
            TracesHandlerConfig{.mMaxTraceAge = 10, .mDecayRate = 0.1f},
            shot_cooldown};
  }
};

struct TankTest : TankTestData, ::testing::Test {
  Tank mTankSUT{create_tank(std::move(mEngine))};

  float mSpeed{1.f};
  int mAngle{90};
};

TEST_F(TankTest, GivenAngleRotationWhenUpdateThenShouldCallGetPositionDeltaWithAngleRotation) {
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(mAngle)));
  mTankSUT.set_rotation(mAngle);

  mTankSUT.update();
}

TEST_F(TankTest, Given1UpdateWhenGetPositionThenReturnsPositionDelta) {
  const sf::Vector2f expected_position = {0.f, 10.f};
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillOnce(testing::Return(expected_position));

  mTankSUT.update();

  expect_vec2f_eq(expected_position, mTankSUT.get_position());
}

TEST_F(TankTest, GivenMultipleUpdatesWhenGetPositionThenReturnsPositionDeltaSum) {
  const sf::Vector2f single_move = {3.f, 5.f};
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillRepeatedly(testing::Return(single_move));
  const int update_count = 3;
  const sf::Vector2f expected_position = {9.f, 15.f};

  update_many(mTankSUT, update_count);

  expect_vec2f_eq(expected_position, mTankSUT.get_position());
}

TEST_F(TankTest, RotateTower_ShouldntAffectMoving) {
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(mAngle)));
  mTankSUT.set_rotation(mAngle);

  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.update();
}

TEST_F(TankTest, WhenTankMoves_ThenItShouldNotMoveOutOfTheBoard) {
  mAngle = 315.f;
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(mAngle)))
      .WillRepeatedly(testing::Return(sf::Vector2f{-5.f, -5.f}));
  mTankSUT.set_rotation(mAngle);
  mTankSUT.set_gear(Gear::Drive);

  update_many(mTankSUT, 100);

  expect_vec2f_eq({0.f, 0.f}, mTankSUT.get_position());
}

TEST_F(TankTest, WhenTankIsOneAxisOutOfTheBoard_ThenShouldAllowToMoveOnlyOneAxis) {
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(testing::_))
      .WillRepeatedly(testing::Return(sf::Vector2f{-5.f, 5.f}));
  mTankSUT.set_gear(Gear::Drive);

  update_many(mTankSUT, 100);

  expect_vec2f_eq({0.f, 500.f}, mTankSUT.get_position());
}

TEST_F(TankTest, WhenTankTakesHitForZeroDamage_ThenShouldBeAlive) {
  mTankSUT.take_damage(0);
  EXPECT_TRUE(mTankSUT.is_alive());
}

TEST_F(TankTest, WhenTankTakesTwoHitsForHalfHealth_ThenShouldNotBeAliveAfterSecondOne) {
  auto half_health = health / 2u;
  mTankSUT.take_damage(half_health);
  EXPECT_TRUE(mTankSUT.is_alive());
  mTankSUT.take_damage(health - half_health);
  EXPECT_FALSE(mTankSUT.is_alive());
}

TEST_F(TankTest, WhenTankTakesHitForWholeHealth_ThenShouldNotBeAlive) {
  mTankSUT.take_damage(health);
  EXPECT_FALSE(mTankSUT.is_alive());
}

struct TankShootingTest : TankTestData, ::testing::TestWithParam<float> {
  Tank mTankSUT{create_tank(std::move(mEngine))};
};

TEST_P(TankShootingTest, GivenAnyRotation_WhenTankShoots_ThenTankBodyShouldNotContainMissile) {
  const auto rotation = GetParam();
  mTankSUT.set_rotation(rotation);
  const auto& missile = mTankSUT.shoot();

  EXPECT_FALSE(mTankSUT.get_body_rect().contains(missile->get_pos()));
}

INSTANTIATE_TEST_SUITE_P(TankShootingTestsWithManyValues, TankShootingTest,
                         testing::Values(0.f, 30.f, 45.f, 60.f, 90.f, 135.f, 180.f, 225.f, 270.f,
                                         315.f, 359.f));
