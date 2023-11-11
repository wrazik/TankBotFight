#include <gtest/gtest.h>

#include <memory>

#include "Sound.hpp"
#include "Tank/TankTurret.hpp"
#include "TestUtility.hpp"

class TankTurretTest : public ::testing::Test {
 public:
  std::unique_ptr<sf::Texture> mTurretTex{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mShotTex{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mMissileTex{create_dummy_texture()};
  TankTurretTextures mTextures{
      .mTurret = *mTurretTex, .mShotAnimation = *mShotTex, .mMissile = *mMissileTex};
};

TEST_F(TankTurretTest, Given0MsCooldown_WhenShotCalled_ThenMissileIsAlwaysReturned) {
  TankTurret mTurret{mTextures, std::chrono::milliseconds{0}, Sound{"tank_shot.flac"}};
  EXPECT_TRUE(mTurret.shoot());
  EXPECT_TRUE(mTurret.shoot());
  EXPECT_TRUE(mTurret.shoot());
}

TEST_F(TankTurretTest, GivenNonZeroCooldown_WhenShotCalled_ThenMissileIsNotAlwaysReturned) {
  TankTurret mTurret{mTextures, std::chrono::milliseconds{500}, Sound{"tank_shot.flac"}};
  EXPECT_TRUE(mTurret.shoot());
  EXPECT_FALSE(mTurret.shoot());
  EXPECT_FALSE(mTurret.shoot());
}
