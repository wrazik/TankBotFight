#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <memory>

#include "Engine.hpp"
#include "TextureStore.hpp"
#include "TracesHandler.hpp"

enum class Rotation { None, Clockwise, Counterclockwise };

class TankPart {
 public:
  explicit TankPart(sf::Texture& texture);

  void rotate(Rotation r);
  void set_rotation(float angle);
  void draw(sf::RenderWindow& window, float x, float y);
  float get_rotation() const;
  sf::Sprite& get_sprite();
  const sf::Sprite& get_sprite() const;
  void update();

 private:
  sf::Sprite mSprite;
  Rotation mRotation = Rotation::None;
};

class Tank {
 public:
  Tank(float x, float y, sf::Texture& body, sf::Texture& tower, sf::Texture& shot,
       sf::Texture& tracks, std::unique_ptr<Engine>&& engine,
       const TracesHandlerConfig& traces_handler_config = TracesHandlerConfig{});
  Tank(const Tank& rhs);
  Tank(Tank&& rhs) noexcept;
  Tank& operator=(const Tank& rhs);
  Tank& operator=(Tank&& rhs) noexcept;
  ~Tank() = default;

  void rotate_body(Rotation r);
  void rotate_tower(Rotation r);
  void set_rotation(int angle);

  void set_gear(Gear gear);
  void draw(sf::RenderWindow& window);
  void update();
  void shot();

  float get_tower_rotation() const;
  sf::Vector2f get_position();
  float get_current_speed();

 private:
  inline constexpr static float M_SPEED = 0.01f;
  void update_shot();
  void update_position();
  void draw_shot(sf::RenderWindow& window);
  void draw_tracks(sf::RenderWindow& window);

  sf::Vector2f mPos;
  float mCurrentSpeed = 0.0f;
  std::chrono::system_clock::time_point mShotStart;
  bool mDrawShot = false;

  TankPart mBody;
  TankPart mTower;
  TankPart mShot;
  std::unique_ptr<Engine> mEngine;
  std::unique_ptr<TracesHandler> mTracesHandler;
};
