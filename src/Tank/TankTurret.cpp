#include "TankTurret.hpp"

#include <gsl/gsl>

#include "utility.hpp"

constexpr int ROTATION_OFFSET = 90;
constexpr int SHOT_ANIMATION_DISTANCE = 30;
constexpr std::chrono::milliseconds SHOT_ANIMATION_DURATION = std::chrono::milliseconds(100);
constexpr auto SHOT_COOLDOWN = std::chrono::milliseconds{500};
constexpr unsigned int MISSLE_DAMAGE = 20;

TankTurret::TankTurret(const TankTurretTextures& textures,
                     const std::chrono::milliseconds& shot_cooldown, Sound&& shot_sound)
    : mTurret(textures.mTurret),
      mShotAnimation(textures.mShotAnimation),
      mMissileTexture(textures.mMissile),
      mShotSound(std::move(shot_sound)),
      mShotCooldown(shot_cooldown) {}

void TankTurret::set_position(const sf::Vector2f& pos) {
  mTurret.get_sprite().setPosition(pos);
  mShotAnimation.get_sprite().setPosition(calculate_shot_position());
}

sf::Vector2f TankTurret::calculate_shot_position() const {
  const auto turret_rotation = mTurret.get_rotation();
  const auto& [x, y] = mTurret.get_sprite().getPosition();
  return sf::Vector2f{
      x + SHOT_ANIMATION_DISTANCE *
              gsl::narrow_cast<float>(cos(to_radians(turret_rotation - ROTATION_OFFSET))),
      y + SHOT_ANIMATION_DISTANCE *
              gsl::narrow_cast<float>(sin(to_radians(turret_rotation - ROTATION_OFFSET)))};
}

void TankTurret::set_rotation(float angle) {
  mTurret.set_rotation(angle);
  mShotAnimation.set_rotation(angle);
}

void TankTurret::rotate(Rotation r) {
  mTurret.rotate(r);
  mShotAnimation.rotate(r);
}

void TankTurret::draw(sf::RenderWindow& window) {
  mTurret.draw(window);
  if (mDrawShot) {
    mShotAnimation.draw(window);
  }
}

void TankTurret::update() {
  mTurret.update();
  mShotAnimation.update();
  update_shot_time();
}

void TankTurret::update_shot_time() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
  if (elapsed > SHOT_ANIMATION_DURATION) {
    mDrawShot = false;
  }
}

std::optional<Missle> TankTurret::shoot() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
  if (elapsed >= mShotCooldown) {
    mLastShot = std::chrono::system_clock::now();
    mDrawShot = true;
    mShotSound.play();
    const auto& [x, y] = calculate_shot_position();
    return std::make_optional<Missle>(
        mMissileTexture, MovementState{.mX = x, .mY = y, .mAngle = mTurret.get_rotation()},
        MISSLE_DAMAGE);
  }
  return std::nullopt;
}

float TankTurret::get_rotation() const { return mTurret.get_rotation(); }
