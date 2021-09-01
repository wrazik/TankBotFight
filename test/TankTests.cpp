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
  MOCK_METHOD(float, get_current_speed, (), (const, override));
  MOCK_METHOD(sf::Vector2f, get_position_delta, (float), (override));
  MOCK_METHOD(void, update, (), (override));
  MOCK_METHOD(void, set_gear, (Gear), (override));
};

struct TankTest : ::testing::Test {
  sf::Texture mBody;
  sf::Texture mTower;
  sf::Texture mShot;
  Tank mTankSUT;

  float speed;
  int angle;

  TankTest()
      : mBody(create_dummy_texture()),
        mTower(create_dummy_texture()),
        mShot(create_dummy_texture()),
        mTankSUT(create_tank(std::make_unique<testing::StrictMock<EngineMock>>())),
        speed{1.f},
        angle{90} {}

  Tank create_tank(std::unique_ptr<testing::NiceMock<EngineMock>> engine) {
    return Tank(0, 0, mBody, mTower, mShot, std::move(engine));
  }

  Tank create_tank(std::unique_ptr<testing::StrictMock<EngineMock>> engine) {
    return Tank(0, 0, mBody, mTower, mShot, std::move(engine));
  }
};

TEST_F(TankTest, GivenAngleRotationWhenUpdateThenShouldCallGetPositionDeltaWithAngleRotation) {
  auto mEngineNiceMock = std::make_unique<testing::NiceMock<EngineMock>>();
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(angle)));
  Tank mTankSUT = create_tank(std::move(mEngineNiceMock));
  mTankSUT.set_rotation(angle);

  mTankSUT.update();
}

TEST_F(TankTest, Given1UpdateWhenGetPositionThenReturnsPositionDelta) {
  sf::Vector2f expectedPosition = {0.f, 10.f};
  auto mEngineNiceMock = std::make_unique<testing::NiceMock<EngineMock>>();
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillOnce(testing::Return(expectedPosition));
  Tank mTankSUT = create_tank(std::move(mEngineNiceMock));

  mTankSUT.update();

  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, GivenMultipleUpdatesWhenGetPositionThenReturnsPositionDeltaSum) {
  sf::Vector2f singleMove = {3.f, -7.f};
  auto mEngineNiceMock = std::make_unique<testing::NiceMock<EngineMock>>();
  EXPECT_CALL(*mEngineNiceMock, get_position_delta).WillRepeatedly(testing::Return(singleMove));
  Tank mTankSUT = create_tank(std::move(mEngineNiceMock));
  int updateCount = 3;
  sf::Vector2f expectedPosition = {9.f, -21.f};

  update_many(mTankSUT, updateCount);

  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, RotateTower_ShouldntAffectMoving) {
  auto mEngineNiceMock = std::make_unique<testing::NiceMock<EngineMock>>();
  EXPECT_CALL(*mEngineNiceMock, get_position_delta(to_radians(angle)));
  Tank mTankSUT = create_tank(std::move(mEngineNiceMock));
  mTankSUT.set_rotation(angle);

  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.update();
}
