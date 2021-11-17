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

float get_trace_rotation(const std::deque<Trace>& traces, int idx) {
  return traces[idx].get_rotation();
}

float get_trace_height(const std::deque<Trace>& traces, int idx) {
  return traces[idx].get_height();
}

class BaseFixture {
 protected:
  unsigned int mWidth{10};
  unsigned int mHeight{20};
  sf::Vector2f mStartPosition{0.f, 0.f};
  std::unique_ptr<sf::Texture> mTexture{create_dummy_texture(mWidth, mHeight)};
  int mMaxTracesAge{10};
  float mTraceDecayRate{0.1f};
  sf::Sprite mTankSprite{set_up_sprite(*mTexture, mStartPosition)};
  TracesHandler mHandler{*mTexture, mTankSprite, mStartPosition, mMaxTracesAge, mTraceDecayRate};
};

class TracesHandlerRotationTest : public BaseFixture,
                                  public ::testing::TestWithParam<std::pair<sf::Vector2f, float>> {

};

TEST_P(TracesHandlerRotationTest, GivenMove_ThenTraceShouldHaveOppositeRotation) {
  const auto& [move, expected_rotation] = GetParam();

  mTankSprite.move(move);
  mHandler.update();
  const auto& actual_traces = mHandler.get_traces();

  ASSERT_EQ(1, actual_traces.size());
  EXPECT_NEAR(expected_rotation, get_trace_rotation(actual_traces, 0), PRECISION);
}

INSTANTIATE_TEST_CASE_P(RotationTestsWithManyValues, TracesHandlerRotationTest,
                        ::testing::Values(std::make_pair(sf::Vector2f{2.f, 0.f}, 270.f),
                                          std::make_pair(sf::Vector2f{2.f, 2.f}, 315.f),
                                          std::make_pair(sf::Vector2f{0.f, 2.f}, 0.f),
                                          std::make_pair(sf::Vector2f{-2.f, 2.f}, 45.f),
                                          std::make_pair(sf::Vector2f{-2.f, -2.f}, 135.f)));

class TracesHandlerTextureHeightTest
    : public BaseFixture,
      public ::testing::TestWithParam<std::pair<sf::Vector2f, float>> {};

TEST_P(TracesHandlerTextureHeightTest, GivenMove_ThenTraceShouldHaveHeightEqualToMoveHypot) {
  const auto& [move, expected_height] = GetParam();

  mTankSprite.move(move);
  mHandler.update();
  const auto& actual_traces = mHandler.get_traces();

  ASSERT_EQ(1, actual_traces.size());
  EXPECT_NEAR(expected_height, get_trace_height(actual_traces, 0), PRECISION);
}

INSTANTIATE_TEST_CASE_P(TextureHeightTestsWithManyValues, TracesHandlerTextureHeightTest,
                        ::testing::Values(std::make_pair(sf::Vector2f{2.f, 0.f}, 2),
                                          std::make_pair(sf::Vector2f{1.f, 1.f}, 1.4142f),
                                          std::make_pair(sf::Vector2f{3.f, 4.f}, 5),
                                          std::make_pair(sf::Vector2f{6.f, 8.f}, 10),
                                          std::make_pair(sf::Vector2f{0.f, -2.f}, 2)));

class TracesHandlerTest : public BaseFixture, public ::testing::Test {};

TEST_F(TracesHandlerTest, GivenFreshTracesHandler_ThenTracesShouldBeEmpty) {
  auto actual_traces = mHandler.get_traces();

  EXPECT_TRUE(actual_traces.empty());
}

TEST_F(TracesHandlerTest, GivenMovesWithSameAngle_ThenTraceShouldHaveHeightEqualToSumOfMoveHypot) {
  sf::Vector2f move1{1.f, 1.f};
  sf::Vector2f move2{2.f, 2.f};
  const float expected_height = 4.2426f;

  mTankSprite.move(move1);
  mHandler.update();
  mTankSprite.move(move2);
  mHandler.update();

  const auto& actual_traces = mHandler.get_traces();

  ASSERT_EQ(1, actual_traces.size());
  ASSERT_NEAR(expected_height, get_trace_height(actual_traces, 0), PRECISION);
}

TEST_F(TracesHandlerTest,
       GivenMovesWithDifferentAngle_ThenAddSeperateTracesWithHeightEqualToMoveHypot) {
  sf::Vector2f move1{6.f, 0.f};
  sf::Vector2f move2{0.f, 14.f};
  sf::Vector2f move3{-3.f, 4.f};
  const float expected_height1 = 6;
  const float expected_height2 = 14;
  const float expected_height3 = 5;

  mTankSprite.move(move1);
  mHandler.update();
  mTankSprite.move(move2);
  mHandler.update();
  mTankSprite.move(move3);
  mHandler.update();

  const auto& actual_traces = mHandler.get_traces();

  ASSERT_EQ(3, actual_traces.size());
  ASSERT_NEAR(expected_height1, get_trace_height(actual_traces, 0), PRECISION);
  ASSERT_NEAR(expected_height2, get_trace_height(actual_traces, 1), PRECISION);
  ASSERT_NEAR(expected_height3, get_trace_height(actual_traces, 2), PRECISION);
}

TEST_F(TracesHandlerTest,
       WhenTraceAgeIsGreaterThanMaxAge_ThenTraceHeightShouldDecreaseByDecayRate) {
  sf::Vector2f move1{30.f, 0.f};
  const float expected_height1 = 30.f;
  const float expected_height2 = 28.f;
  const float expected_height3 = 26.f;
  const float expected_height4 = 24.f;
  const auto& actual_traces = mHandler.get_traces();

  mTankSprite.move(move1);
  update_many(mHandler, mMaxTracesAge);
  const float actual_height1 = get_trace_height(actual_traces, 0);
  mHandler.update();
  const float actual_height2 = get_trace_height(actual_traces, 0);
  mHandler.update();
  const float actual_height3 = get_trace_height(actual_traces, 0);
  mHandler.update();
  const float actual_height4 = get_trace_height(actual_traces, 0);

  ASSERT_EQ(1, actual_traces.size());
  ASSERT_NEAR(expected_height1, actual_height1, PRECISION);
  ASSERT_NEAR(expected_height2, actual_height2, PRECISION);
  ASSERT_NEAR(expected_height3, actual_height3, PRECISION);
  ASSERT_NEAR(expected_height4, actual_height4, PRECISION);
}

TEST_F(TracesHandlerTest, WhenTraceHeightIsEqualOrLowerThanDecayValue_ThenRemoveTrace) {
  sf::Vector2f move1{2.f, 0.f};
  const int expected_size1 = 1;
  const int expected_size2 = 0;

  mTankSprite.move(move1);
  update_many(mHandler, mMaxTracesAge);
  const auto actual_size1 = mHandler.get_traces().size();
  mHandler.update();
  const auto actual_size2 = mHandler.get_traces().size();

  ASSERT_EQ(expected_size1, actual_size1);
  ASSERT_EQ(expected_size2, actual_size2);
}
