#include <gtest/gtest.h>

#include "TestUtility.hpp"
#include "TracesHandler.hpp"
#include "utility.hpp"

sf::Sprite setUpSprite(sf::Texture& tex) {
  sf::Sprite sprite(tex);
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  sprite.setOrigin(width / 2, height / 2);
  sprite.setPosition({0.f, 0.f});
  sprite.setRotation(0.f);
  return sprite;
}

void moveSprite(sf::Sprite& sprite, const sf::Vector2f& move) {
  sprite.move(move);
  sprite.setRotation(get_angle(move));
}

class TracesHandlerTest : public ::testing::Test {
 protected:
  uint mWidth{10};
  uint mHeight{20};
  sf::Vector2f mStartPosition{0.f, 0.f};
  std::unique_ptr<sf::Texture> mTexture{create_dummy_texture(mWidth, mHeight)};
  sf::Sprite mTankSprite{setUpSprite(*mTexture)};
  TracesHandler mHandler{*mTexture, mTankSprite};
};

TEST_F(TracesHandlerTest, GivenFreshTracesHandler_ThenTracesShouldBeEmpty) {
  auto actualTraces = mHandler.getTraces();

  EXPECT_TRUE(actualTraces.empty());
}

TEST_F(TracesHandlerTest, GivenMove_ThenTracesShouldContainSpriteWithHeightEqualToMoveHypot) {
  sf::Vector2f move{3.f, 4.f};
  mTankSprite.move(move);
  mHandler.update();
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
  mTankSprite.move(move);
  mHandler.update();
  mTankSprite.move(move);
  mHandler.update();
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
  sf::Vector2f move1{6.f, 0.f};
  sf::Vector2f move2{0.f, 14.f};
  moveSprite(mTankSprite, move1);
  mHandler.update();
  moveSprite(mTankSprite, move2);
  mHandler.update();
  const float expectedRotation1 = 90.f;
  const float expectedRotation2 = 180.f;
  const float expectedHeight1 = 6.f;
  const float expectedHeight2 = 14.f;
  const sf::Vector2f expectedPosition1 = {-4.f, 0.f};
  const sf::Vector2f expectedPosition2 = {6.f, 4.f};
  const auto& actualTraces = mHandler.getTraces();

  ASSERT_EQ(2, actualTraces.size());
  const float actualSpriteRotation1 = actualTraces[0].getRotation();
  const float actualSpriteRotation2 = actualTraces[1].getRotation();
  const auto actualSpriteHeight1 = actualTraces[0].getTextureRect().height;
  const auto actualSpriteHeight2 = actualTraces[1].getTextureRect().height;
  const auto actualSpritePosition1 = actualTraces[0].getPosition();
  const auto actualSpritePosition2 = actualTraces[1].getPosition();

  EXPECT_EQ(expectedRotation1, actualSpriteRotation1);
  EXPECT_EQ(expectedRotation2, actualSpriteRotation2);
  EXPECT_EQ(expectedHeight1, actualSpriteHeight1);
  EXPECT_EQ(expectedHeight2, actualSpriteHeight2);
  expect_vec2f_eq(expectedPosition1, actualSpritePosition1);
  expect_vec2f_eq(expectedPosition2, actualSpritePosition2);
}
