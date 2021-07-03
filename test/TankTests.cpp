#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <utility>

#include "Tank.hpp"

static sf::Texture create_dummy_texture() {
  sf::Texture dummy;
  dummy.create(5, 5);
  return dummy;
}

struct TankTest : ::testing::Test {
  TankTest()
      : mBody(create_dummy_texture()), mTower(create_dummy_texture()), mTank(0, 0, mBody, mTower) {}

  sf::Texture mBody;
  sf::Texture mTower;
  sf::RenderWindow dummy;
  Tank mTank;
};

void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
  const auto [x1, y1] = lhs;
  const auto [x2, y2] = rhs;
  EXPECT_NEAR(x1, x2, 0.0001);
  EXPECT_NEAR(y1, y2, 0.0001);
}

TEST_F(TankTest, SetSpeed_ShouldMoveUp) {
  expect_vec2f_eq(mTank.get_position(), {0.f, 0.f});
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {0.f, -10.f});
}

TEST_F(TankTest, Rotate90Degree_ShouldMoveLeft) {
  mTank.set_rotation(90);
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {10.f, 0.f});
}

TEST_F(TankTest, Rotate180Degree_ShouldMoveDown) {
  mTank.set_rotation(180);
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {0.f, 10.f});
}

TEST_F(TankTest, Rotate270Degree_ShouldMoveLeft) {
  mTank.set_rotation(270);
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {-10.f, 0.f});
}

TEST_F(TankTest, MoveUpAndDown_ShouldReturnSamePos) {
  expect_vec2f_eq(mTank.get_position(), {0.f, 0.f});
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  mTank.set_current_speed(-10.0f);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {0.f, 0.f});
}

TEST_F(TankTest, MoveTurn180Move_ShouldReturn) {
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);

  mTank.set_rotation(180);
  mTank.draw(dummy);
  expect_vec2f_eq(mTank.get_position(), {0.f, 0.f});
}

TEST_F(TankTest, MoveSquare_ShouldReturnToStart) {
  mTank.set_current_speed(10.0f);
  mTank.draw(dummy);
  mTank.set_rotation(90);
  mTank.draw(dummy);
  mTank.set_rotation(180);
  mTank.draw(dummy);
  mTank.set_rotation(270);
  mTank.draw(dummy);

  expect_vec2f_eq(mTank.get_position(), {0.f, 0.f});
}

TEST_F(TankTest, RotateTower_ShoudntAffectMoving) {
  mTank.set_current_speed(10.0f);
  mTank.rotate_tower(Rotation::Clockwise);
  mTank.draw(dummy);
  mTank.rotate_tower(Rotation::Counterclockwise);

  expect_vec2f_eq(mTank.get_position(), {0.f, -10.f});
}

TEST_F(TankTest, RotateBody_ShouldAffectMoving) {
  mTank.set_current_speed(10.0f);
  mTank.rotate_body(Rotation::Counterclockwise);
  mTank.draw(dummy);
  mTank.set_current_speed(-10.0f);
  mTank.rotate_body(Rotation::Counterclockwise);
  mTank.draw(dummy);
  mTank.set_current_speed(10.0f);
  mTank.rotate_body(Rotation::Counterclockwise);
  mTank.draw(dummy);

  const auto [x, y] = mTank.get_position();
  EXPECT_PRED_FORMAT2(testing::FloatLE, x, 0.f);
  EXPECT_PRED_FORMAT2(testing::FloatLE, -10.f, y);
}
