#include <gtest/gtest.h>

#include <memory>

#include "Tank/TankPart.hpp"
#include "TestUtility.hpp"

class TankPartTest : public ::testing::Test {
 public:
  std::unique_ptr<sf::Texture> mTexture{create_dummy_texture()};
  TankPart mPart{*mTexture};
  TankPartTest() {
    constexpr float INITIAL_ROTATION = 100.f;
    mPart.set_rotation(INITIAL_ROTATION);
  }
};

TEST_F(TankPartTest, GivenRotateClockwise_WhenUpdateCalled_ThenRotationShouldBeIncreased) {
  const auto& original_rotation = mPart.get_rotation();
  mPart.rotate(Rotation::Clockwise);
  mPart.update();
  EXPECT_GT(mPart.get_rotation(), original_rotation);
}

TEST_F(TankPartTest, GivenRotateCounterclockwise_WhenUpdateCalled_ThenRotationShouldBeDecreased) {
  const auto& original_rotation = mPart.get_rotation();
  mPart.rotate(Rotation::Counterclockwise);
  mPart.update();
  EXPECT_LT(mPart.get_rotation(), original_rotation);
}

TEST_F(TankPartTest, GivenRotateNone_WhenUpdateCalled_ThenRotationShouldNotChange) {
  const auto& original_rotation = mPart.get_rotation();
  mPart.rotate(Rotation::None);
  mPart.update();
  EXPECT_NEAR(mPart.get_rotation(), original_rotation, PRECISION);
}
