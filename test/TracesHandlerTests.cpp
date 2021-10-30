#include <gtest/gtest.h>

#include "TestUtility.hpp"
#include "TracesHandler.hpp"
#include "utility.hpp"

sf::Sprite set_up_sprite(sf::Texture& tex, const sf::Vector2f& startPosition) {
  sf::Sprite sprite(tex);
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  sprite.setOrigin(width / 2, height / 2);
  sprite.setPosition(startPosition);
  sprite.setRotation(0.f);
  return sprite;
}

float get_trace_rotation(const std::deque<sf::Sprite>& traces, int idx) {
  return traces[idx].getRotation();
}

int get_trace_height(const std::deque<sf::Sprite>& traces, int idx) {
  return traces[idx].getTextureRect().height;
}

class BaseFixture {
 protected:
  uint mWidth{10};
  uint mHeight{20};
  sf::Vector2f mStartPosition{0.f, 0.f};
  std::unique_ptr<sf::Texture> mTexture{create_dummy_texture(mWidth, mHeight)};
  sf::Sprite mTankSprite{set_up_sprite(*mTexture, mStartPosition)};
  TracesHandler mHandler{*mTexture, mTankSprite, mStartPosition};
};

class TracesHandlerRotationTest : public BaseFixture,
                                  public ::testing::TestWithParam<std::pair<sf::Vector2f, float>> {

};

TEST_P(TracesHandlerRotationTest, GivenMove_ThenTraceShouldHaveOppositeRotation) {
  const auto& [move, expected_rotation] = GetParam();

  mTankSprite.move(move);
  mHandler.update();
  const auto& actual_traces = mHandler.getTraces();

  ASSERT_EQ(1, actual_traces.size());
  EXPECT_NEAR(expected_rotation, get_trace_rotation(actual_traces, 0), precision);
}

INSTANTIATE_TEST_CASE_P(RotationTestsWithManyValues, TracesHandlerRotationTest,
                        ::testing::Values(std::make_pair(sf::Vector2f{2.f, 0.f}, 270.f),
                                          std::make_pair(sf::Vector2f{2.f, 2.f}, 315.f),
                                          std::make_pair(sf::Vector2f{0.f, 2.f}, 0.f),
                                          std::make_pair(sf::Vector2f{-2.f, 2.f}, 45.f),
                                          std::make_pair(sf::Vector2f{-2.f, -2.f}, 135.f)));

class TracesHandlerTextureHeightTest
    : public BaseFixture,
      public ::testing::TestWithParam<std::pair<sf::Vector2f, int>> {};

TEST_P(TracesHandlerTextureHeightTest, GivenMove_ThenTraceShouldHaveHeightEqualToMoveHypot) {
  const auto& [move, expected_height] = GetParam();

  mTankSprite.move(move);
  mHandler.update();
  const auto& actual_traces = mHandler.getTraces();

  ASSERT_EQ(1, actual_traces.size());
  EXPECT_NEAR(expected_height, get_trace_height(actual_traces, 0), precision);
}

INSTANTIATE_TEST_CASE_P(TextureHeightTestsWithManyValues, TracesHandlerTextureHeightTest,
                        ::testing::Values(std::make_pair(sf::Vector2f{2.f, 0.f}, 2),
                                          std::make_pair(sf::Vector2f{1.f, 1.f}, 1),
                                          std::make_pair(sf::Vector2f{3.f, 4.f}, 5),
                                          std::make_pair(sf::Vector2f{6.f, 8.f}, 10),
                                          std::make_pair(sf::Vector2f{0.f, -2.f}, 2)));

class TracesHandlerTest : public BaseFixture, public ::testing::Test {};

TEST_F(TracesHandlerTest, GivenFreshTracesHandler_ThenTracesShouldBeEmpty) {
  auto actual_traces = mHandler.getTraces();

  EXPECT_TRUE(actual_traces.empty());
}

TEST_F(TracesHandlerTest,
       GivenMovesWithSameAngle_ThenTraceShouldHaveHeightEqualToSumOfMoveHypotWithValueRounding) {
  sf::Vector2f move1{1.f, 1.f};
  sf::Vector2f move2{2.f, 2.f};
  const int expected_height = 4;

  mTankSprite.move(move1);
  mHandler.update();
  mTankSprite.move(move2);
  mHandler.update();

  const auto& actual_traces = mHandler.getTraces();

  ASSERT_EQ(1, actual_traces.size());
  EXPECT_EQ(expected_height, get_trace_height(actual_traces, 0));
}

TEST_F(TracesHandlerTest,
       GivenMovesWithDifferentAngle_ThenAddSeperateTracesWithHeightEqualToMoveHypot) {
  sf::Vector2f move1{6.f, 0.f};
  sf::Vector2f move2{0.f, 14.f};
  sf::Vector2f move3{-3.f, 4.f};
  const int expected_height1 = 6;
  const int expected_height2 = 14;
  const int expected_height3 = 5;

  mTankSprite.move(move1);
  mHandler.update();
  mTankSprite.move(move2);
  mHandler.update();
  mTankSprite.move(move3);
  mHandler.update();

  const auto& actual_traces = mHandler.getTraces();

  ASSERT_EQ(3, actual_traces.size());
  EXPECT_EQ(expected_height1, get_trace_height(actual_traces, 0));
  EXPECT_EQ(expected_height2, get_trace_height(actual_traces, 1));
  EXPECT_EQ(expected_height3, get_trace_height(actual_traces, 2));
}

TEST_F(TracesHandlerTest,
       GivenMoveLongerThanMaxTextureHeight_ThenSetCurrentSpriteHeightToMaxAndAddNewTrace) {
  const float max_height = mHandler.get_max_texture_height();
  sf::Vector2f move1{max_height - 1.f, 0.f};
  sf::Vector2f move2{2.f, 0.f};
  const int expected_height1 = max_height;
  const int expected_height2 = 1.f;

  mTankSprite.move(move1);
  mHandler.update();
  mTankSprite.move(move2);
  mHandler.update();

  const auto& actual_traces = mHandler.getTraces();

  ASSERT_EQ(2, actual_traces.size());
  EXPECT_EQ(expected_height1, get_trace_height(actual_traces, 0));
  EXPECT_EQ(expected_height2, get_trace_height(actual_traces, 1));
}
