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
  MOCK_METHOD(void, set_speed, (float), (override));
  MOCK_METHOD(float, get_current_speed, (), (const, override));
  MOCK_METHOD(sf::Vector2f, get_position_delta, (float), (override));
  MOCK_METHOD(void, update, (), (override));
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

TEST_F(TankTest, SetSpeed_ShouldCallEngineSetSpeed) {
  EXPECT_CALL(mEngineStrictMock, set_speed(speed));
  
  mTankSUT.set_speed(speed);
}

TEST_F(TankTest, GivenAngleRotationWhenUpdateThenShouldCallGetPositionDeltaWithAngleRotation) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  mTankSUT.set_rotation(angle);
  EXPECT_CALL(mEngineNiceMock, get_position_delta(to_radians(angle)));
  
  mTankSUT.update();
}

TEST_F(TankTest, GivenSpeedWhenUpdateThenTankChangesPosition) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  sf::Vector2f expectedPosition = {0.f, 10.f};
  EXPECT_CALL(mEngineNiceMock, get_position_delta).WillOnce(testing::Return(expectedPosition));
  
  mTankSUT.set_speed(speed);
  mTankSUT.update();
  
  expect_vec2f_eq(expectedPosition, mTankSUT.get_position());
}

TEST_F(TankTest, RotateTower_ShouldntAffectMoving) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  sf::Vector2f expectedMove = {0.f, 10.f};
  mTankSUT.set_rotation(angle);
  EXPECT_CALL(mEngineNiceMock, get_position_delta(to_radians(angle)))
      .WillOnce(testing::Return(expectedMove));
  mTankSUT.set_speed(speed);

  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.rotate_tower(Rotation::Clockwise);
  mTankSUT.update();

  expect_vec2f_eq(mTankSUT.get_position(), expectedMove);
}

TEST_F(TankTest, RotateBody_ShouldAffectMoving) {
  Tank mTankSUT = create_tank(mEngineNiceMock);
  const auto [original_x, original_y] = mTankSUT.get_position();
  angle = 0;
  mTankSUT.set_rotation(angle);
  mTankSUT.set_speed(speed);
  
  mTankSUT.rotate_body(Rotation::Counterclockwise);
  mTankSUT.update();
  mTankSUT.rotate_body(Rotation::Counterclockwise);
  mTankSUT.update();
  mTankSUT.rotate_body(Rotation::Counterclockwise);
  mTankSUT.update();

  const auto [actual_x, actual_y] = mTankSUT.get_position();
  EXPECT_PRED_FORMAT2(testing::FloatLE, actual_x, original_x);
  EXPECT_PRED_FORMAT2(testing::FloatLE, actual_y, original_y);
}
