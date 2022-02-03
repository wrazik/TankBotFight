#pragma once
#include <chrono>
#include <functional>
#include <optional>

#include "Missle.hpp"
#include "SFML/Graphics.hpp"
#include "Tank/TankPart.hpp"

struct TankTowerTextures {
  std::reference_wrapper<sf::Texture> mTower;
  std::reference_wrapper<sf::Texture> mShotAnimation;
  std::reference_wrapper<sf::Texture> mMissile;
};

class TankTower {
 public:
  TankTower(const TankTowerTextures& textures, const std::chrono::milliseconds& shot_cooldown);

  void set_position(const sf::Vector2f& pos);
  void set_rotation(float angle);
  void rotate(Rotation r);

  void draw(sf::RenderWindow& window);
  void update();

  [[nodiscard]] std::optional<Missle> shot();
  [[nodiscard]] float get_rotation() const;

 private:
  sf::Vector2f calculate_shot_position() const;
  void update_shot_time();

  TankPart mTower;
  TankPart mShotAnimation;
  std::reference_wrapper<sf::Texture> mMissileTexture;
  std::chrono::time_point<std::chrono::system_clock> mLastShot;
  std::chrono::milliseconds mShotCooldown;
  bool mDrawShot = false;
};
