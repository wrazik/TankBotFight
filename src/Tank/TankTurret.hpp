#pragma once
#include <chrono>
#include <functional>
#include <optional>

#include "Missle.hpp"
#include "SFML/Graphics.hpp"
#include "Sound.hpp"
#include "Tank/TankPart.hpp"

struct TankTurretTextures {
  std::reference_wrapper<sf::Texture> mTurret;
  std::reference_wrapper<sf::Texture> mShotAnimation;
  std::reference_wrapper<sf::Texture> mMissile;
};

class TankTurret {
 public:
  TankTurret(const TankTurretTextures& textures, const std::chrono::milliseconds& shot_cooldown,
            Sound&& shot_sound);

  void set_position(const sf::Vector2f& pos);
  void set_rotation(float angle);
  void rotate(Rotation r);

  void draw(sf::RenderWindow& window);
  void update();

  [[nodiscard]] std::optional<Missle> shoot();
  [[nodiscard]] float get_rotation() const;

 private:
  sf::Vector2f calculate_shot_position() const;
  void update_shot_time();

  TankPart mTurret;
  TankPart mShotAnimation;
  Sound mShotSound;
  std::reference_wrapper<sf::Texture> mMissileTexture;
  std::chrono::time_point<std::chrono::system_clock> mLastShot;
  std::chrono::milliseconds mShotCooldown;
  bool mDrawShot = false;
};
