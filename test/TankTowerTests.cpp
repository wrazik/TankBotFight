#include <gtest/gtest.h>

#include <memory>

#include "Sound.hpp"
#include "Tank/TankTower.hpp"
#include "TestUtility.hpp"

class TankTowerTest : public ::testing::Test {
 public:
  std::unique_ptr<sf::Texture> mTowerTex{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mShotTex{create_dummy_texture()};
  std::unique_ptr<sf::Texture> mMissileTex{create_dummy_texture()};
  TankTowerTextures mTextures{
      .mTower = *mTowerTex, .mShotAnimation = *mShotTex, .mMissile = *mMissileTex};
  Sound mShotSound{"tank_shot.flac"};
};

TEST_F(TankTowerTest, Given0MsCooldown_WhenShotCalled_ThenMissileIsAlwaysReturned) {
  TankTower mTower{mTextures, std::chrono::milliseconds{0}, mShotSound};
  EXPECT_TRUE(mTower.shoot());
  EXPECT_TRUE(mTower.shoot());
  EXPECT_TRUE(mTower.shoot());
}

TEST_F(TankTowerTest, GivenNonZeroCooldown_WhenShotCalled_ThenMissileIsNotAlwaysReturned) {
  TankTower mTower{mTextures, std::chrono::milliseconds{500}, mShotSound};
  EXPECT_TRUE(mTower.shoot());
  EXPECT_FALSE(mTower.shoot());
  EXPECT_FALSE(mTower.shoot());
}
