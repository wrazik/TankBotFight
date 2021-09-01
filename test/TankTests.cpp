#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <utility>

#include "SquareRootEngine.hpp"
#include "Tank.hpp"
#include "TestUtility.hpp"
#include "gmock/gmock.h"

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
  testing::StrictMock<EngineMock> mEngineStrictMock;
  testing::NiceMock<EngineMock> mEngineNiceMock;
  Tank mTankSUT;

  float speed;
  int angle;

  TankTest()
      : mBody(create_dummy_texture()),
        mTower(create_dummy_texture()),
        mShot(create_dummy_texture()),
        mTankSUT(create_tank(mEngineStrictMock)),
        speed{1.f},
        angle{90} {}

  Tank create_tank(testing::NiceMock<EngineMock>& engine) {
    return Tank(0, 0, mBody, mTower, mShot, engine);
  }

  Tank create_tank(testing::StrictMock<EngineMock>& engine) {
    return Tank(0, 0, mBody, mTower, mShot, engine);
  }
};


TEST_F(TankTest, GivenAngleRotationWhenUpdateThenShouldCallGetPositionDeltaWithAngleRotation) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  mTankSUT.set_rotation(angle);
  EXPECT_CALL(mEngineNiceMock, get_position_delta(to_radians(angle)));
  
  mTankSUT.update();
}

TEST_F(TankTest, Given1UpdateWhenGetPositionThenReturnsPositionDelta) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  sf::Vector2f expectedPosition = {0.f, 10.f};
  EXPECT_CALL(mEngineNiceMock, get_position_delta).WillOnce(testing::Return(expectedPosition));
  
  mTankSUT.update();
  
  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, GivenMultipleUpdatesWhenGetPositionThenReturnsPositionDeltaSum) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  int updateCount = 3;
  sf::Vector2f expectedPosition = {9.f, -21.f};
  sf::Vector2f singleMove = {3.f, -7.f};
  EXPECT_CALL(mEngineNiceMock, get_position_delta).WillRepeatedly(testing::Return(singleMove));
  
  update_many(mTankSUT, updateCount);
  
  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, RotateTower_ShouldntAffectMoving) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  mTankSUT.set_rotation(angle);
  EXPECT_CALL(mEngineNiceMock, get_position_delta(to_radians(angle)));
  mTankSUT.set_gear(Gear::Drive);

  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.update();
}
