#include <gtest/gtest.h>

#include "TestUtility.hpp"
#include "TracesHandler.hpp"

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

TEST_F(TracesHandlerTest, GivenOneMove_ThenTracesShouldContainSprite) {
  mHandler.update({3.f, 4.f});
  auto actualTraces = mHandler.getTraces();

  EXPECT_EQ(1, actualTraces.size());
}
