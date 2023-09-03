#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <functional>
#include <memory>
#include <optional>

#include "Engine.hpp"
#include "Missle.hpp"
#include "Tank/TankHealthBar.hpp"
#include "Tank/TankPart.hpp"
#include "Tank/TankTower.hpp"
#include "TracesHandler.hpp"

struct TankTextures {
  std::reference_wrapper<sf::Texture> mBody;
  std::reference_wrapper<sf::Texture> mTower;
  std::reference_wrapper<sf::Texture> mShot;
  std::reference_wrapper<sf::Texture> mTracks;
  std::reference_wrapper<sf::Texture> mMissile;
};

class Tank {
 public:
  Tank(float x, float y, const TankTextures& textures, std::unique_ptr<Engine>&& engine,
       const TracesHandlerConfig& traces_handler_config = {},
       const std::chrono::milliseconds& shot_cooldown = std::chrono::milliseconds{500},
       unsigned int health = 100);
  Tank(const Tank& rhs);
  Tank(Tank&& rhs) noexcept;
  Tank& operator=(const Tank& rhs);
  Tank& operator=(Tank&& rhs) noexcept;
  ~Tank() = default;

  void rotate_body(Rotation r);
  void rotate_tower(Rotation r);
  void set_rotation(float angle);
  bool take_hit(unsigned int damage);

  void set_gear(Gear gear);
  void draw(sf::RenderWindow& window);
  void update();

  [[nodiscard]] std::optional<Missle> shoot();
  [[nodiscard]] float get_tower_rotation() const;
  [[nodiscard]] sf::Vector2f get_position() const;
  [[nodiscard]] sf::FloatRect get_body_rect() const;
  [[nodiscard]] float get_current_speed() const;

 private:
  void draw_tracks(sf::RenderWindow& window);
  void update_position();

  sf::Vector2f mPos;
  float mCurrentSpeed = 0.0f;
  int mHealth;

  TankPart mBody;
  TankTower mTower;
  TankHealthBar mHealthBar;
  std::unique_ptr<Engine> mEngine;
  std::unique_ptr<TracesHandler> mTracesHandler;
};
