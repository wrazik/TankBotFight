#include <gtest/gtest.h>

#include "Direction.hpp"
#include "Tank.hpp"

#include <SFML/Graphics.hpp>

struct TankTest : public ::testing::Test
{
  inline static constexpr int START_X = 50;
  inline static constexpr int START_Y = 50;
  inline static constexpr int SPEED = 5;

  Tank mTank = Tank(START_X, START_Y, SPEED);
};

TEST_F(TankTest, MovingUp_ShouldIncreasY)
{
  EXPECT_EQ(mTank.getSprite().getPosition(), (sf::Vector2f{ START_X, START_Y }));
  mTank.move(Direction::Up);
  EXPECT_EQ(mTank.getSprite().getPosition(), (sf::Vector2f{ START_X, START_Y - SPEED }));
}
