#include <gtest/gtest.h>

#include "TestUtility.hpp"
#include "TracesHandler.hpp"
#include "utility.hpp"

class TracesHandlerTest : public ::testing::Test {
 protected:
  uint mWidth{10};
  uint mHeight{20};
  sf::Vector2f mStartPosition{0.f, 0.f};
  std::unique_ptr<sf::Texture> mTexture{create_dummy_texture(mWidth, mHeight)};
  TracesHandler mHandler{*mTexture, mStartPosition};
};

TEST_F(TracesHandlerTest, GivenFreshTracesHandler_ThenTracesShouldBeEmpty) {
  auto actualTraces = mHandler.getTraces();

  EXPECT_TRUE(actualTraces.empty());
}

TEST_F(TracesHandlerTest, GivenMove_ThenTracesShouldContainSpriteWithHeightEqualToMoveHypot) {
  sf::Vector2f move{3.f, 4.f};
  mHandler.update(move);
  const float expectedRotation = get_angle(move);
  const float expectedHeight = 5.f;
  const auto& actualTraces = mHandler.getTraces();

  ASSERT_EQ(1, actualTraces.size());
  const auto actualSpriteRotation = actualTraces.front().getRotation();
  const auto actualSpriteHeight = actualTraces.front().getTextureRect().height;

  EXPECT_EQ(expectedRotation, actualSpriteRotation);
  EXPECT_EQ(expectedHeight, actualSpriteHeight);
}

TEST_F(TracesHandlerTest,
       GivenMovesWithSameAngle_ThenTracesShouldContainSpriteWithHeightEqualToSumOfMoveHypot) {
  sf::Vector2f move{3.f, 4.f};
  mHandler.update(move);
  mHandler.update(move);
  const float expectedRotation = get_angle(move);
  const float expectedHeight = 10.f;
  const auto& actualTraces = mHandler.getTraces();

  ASSERT_EQ(1, actualTraces.size());
  const auto actualSpriteHeight = actualTraces.front().getTextureRect().height;
  const float actualSpriteRotation = actualTraces.front().getRotation();

  EXPECT_EQ(expectedRotation, actualSpriteRotation);
  EXPECT_EQ(expectedHeight, actualSpriteHeight);
}

TEST_F(
    TracesHandlerTest,
    GivenMovesWithDifferentAngle_ThenTracesShouldContainSeperateSpritesWithHeightEqualToMoveHypot) {
  sf::Vector2f move1{6.f, 8.f};
  sf::Vector2f move2{3.f, -4.f};
  mHandler.update(move1);
  mHandler.update(move2);
  const float expectedRotation1 = get_angle(move1);
  const float expectedRotation2 = get_angle(move2);
  const float expectedHeight1 = 10.f;
  const float expectedHeight2 = 5.f;
  const auto& actualTraces = mHandler.getTraces();

  ASSERT_EQ(2, actualTraces.size());
  const float actualSpriteRotation1 = actualTraces[0].getRotation();
  const float actualSpriteRotation2 = actualTraces[1].getRotation();
  const auto actualSpriteHeight1 = actualTraces[0].getTextureRect().height;
  const auto actualSpriteHeight2 = actualTraces[1].getTextureRect().height;

  EXPECT_EQ(expectedRotation1, actualSpriteRotation1);
  EXPECT_EQ(expectedRotation2, actualSpriteRotation2);
  EXPECT_EQ(expectedHeight1, actualSpriteHeight1);
  EXPECT_EQ(expectedHeight2, actualSpriteHeight2);
}
