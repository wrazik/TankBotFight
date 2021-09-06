#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <utility>

#include "SquareRootEngine.hpp"
#include "Tank.hpp"
#include "TestUtility.hpp"
#include "gmock/gmock.h"
#include "utility.hpp"

static sf::Texture create_dummy_texture() {
  sf::Texture dummy;
  dummy.create(5, 5);
  return dummy;
}

struct EngineMock : Engine {
  MOCK_METHOD(void, set_gear, (Gear), (override));
  MOCK_METHOD(float, get_current_speed, (), (const, override));
  MOCK_METHOD(sf::Vector2f, get_position_delta, (float), (override));
  MOCK_METHOD(std::unique_ptr<Engine>, copy, (), (const, override));
  MOCK_METHOD(void, update, (), (override));
};

struct TankTest : ::testing::Test {
  sf::Texture mBody{create_dummy_texture()};
  sf::Texture mTower{create_dummy_texture()};
  sf::Texture mShot{create_dummy_texture()};
  std::unique_ptr<testing::NiceMock<EngineMock>> mEngine{std::make_unique<testing::NiceMock<EngineMock>>()};
  std::shared_ptr<testing::NiceMock<EngineMock>> mEngineNiceMock{std::shared_ptr<testing::NiceMock<EngineMock>>{}, mEngine.get()};
  Tank mTankSUT{create_tank(std::move(mEngine))};

  float mSpeed{1.f};
  int mAngle{90};

  Tank create_tank(std::unique_ptr<testing::NiceMock<EngineMock>>&& engine) {
    return Tank(0, 0, mBody, mTower, mShot, std::move(engine));
  }

  Tank create_tank(std::unique_ptr<testing::StrictMock<EngineMock>>&& engine) {
    return Tank(0, 0, mBody, mTower, mShot, std::move(engine));
  }
};

TEST_F(TankTest, GivenAngleRotationWhenUpdateThenShouldCallGetPositionDeltaWithAngleRotation) {
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(mAngle)));
  mTankSUT.set_rotation(mAngle);

  mTankSUT.update();
}

TEST_F(TankTest, Given1UpdateWhenGetPositionThenReturnsPositionDelta) {
  const sf::Vector2f expectedPosition = {0.f, 10.f};
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillOnce(testing::Return(expectedPosition));

  mTankSUT.update();

  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, GivenMultipleUpdatesWhenGetPositionThenReturnsPositionDeltaSum) {
  const sf::Vector2f singleMove = {3.f, -7.f};
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillRepeatedly(testing::Return(singleMove));
  const int updateCount = 3;
  const sf::Vector2f expectedPosition = {9.f, -21.f};

  update_many(mTankSUT, updateCount);

  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, RotateTower_ShouldntAffectMoving) {
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(mAngle)));
  mTankSUT.set_rotation(mAngle);

  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.update();
}
