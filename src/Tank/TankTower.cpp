#include "TankTower.hpp"

#include <gsl/gsl>

#include "utility.hpp"

constexpr int ROTATION_OFFSET = 90;
constexpr int SHOT_ANIMATION_DISTANCE = 30;
constexpr std::chrono::milliseconds SHOT_ANIMATION_DURATION = std::chrono::milliseconds(100);
constexpr auto SHOT_COOLDOWN = std::chrono::milliseconds{500};
constexpr unsigned int MISSLE_DAMAGE = 20;

TankTower::TankTower(const TankTowerTextures& textures,
                     const std::chrono::milliseconds& shot_cooldown,
                     Sound shot_sound)
    : mTower(textures.mTower),
      mShotAnimation(textures.mShotAnimation),
      mMissileTexture(textures.mMissile),
      mShotSound(shot_sound),
      mShotCooldown(shot_cooldown) {}

void TankTower::set_position(const sf::Vector2f& pos) {
  mTower.get_sprite().setPosition(pos);
  mShotAnimation.get_sprite().setPosition(calculate_shot_position());
}

sf::Vector2f TankTower::calculate_shot_position() const {
  const auto tower_rotation = mTower.get_rotation();
  const auto& [x, y] = mTower.get_sprite().getPosition();
  return sf::Vector2f{
      x + SHOT_ANIMATION_DISTANCE *
              gsl::narrow_cast<float>(cos(to_radians(tower_rotation - ROTATION_OFFSET))),
      y + SHOT_ANIMATION_DISTANCE *
              gsl::narrow_cast<float>(sin(to_radians(tower_rotation - ROTATION_OFFSET)))};
}

void TankTower::set_rotation(float angle) {
  mTower.set_rotation(angle);
  mShotAnimation.set_rotation(angle);
}

void TankTower::rotate(Rotation r) {
  mTower.rotate(r);
  mShotAnimation.rotate(r);
}

void TankTower::draw(sf::RenderWindow& window) {
  mTower.draw(window);
  if (mDrawShot) {
    mShotAnimation.draw(window);
  }
}

void TankTower::update() {
  mTower.update();
  mShotAnimation.update();
  update_shot_time();
}

void TankTower::update_shot_time() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
  if (elapsed > SHOT_ANIMATION_DURATION) {
    mDrawShot = false;
  }
}

std::optional<Missle> TankTower::shoot() {
  
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
  if (elapsed >= mShotCooldown) {
    mLastShot = std::chrono::system_clock::now();
    mDrawShot = true;
    mShotSound.play();
    const auto& [x, y] = calculate_shot_position();
    return std::make_optional<Missle>(
        mMissileTexture, MovementState{.mX = x, .mY = y, .mAngle = mTower.get_rotation()},
        MISSLE_DAMAGE);
  }
  return std::nullopt;
}

float TankTower::get_rotation() const { return mTower.get_rotation(); }
