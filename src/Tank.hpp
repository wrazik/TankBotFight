#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <memory>

#include "Engine.hpp"
#include "TextureStore.hpp"
#include "TracesHandler.hpp"

enum class Rotation { None, Clockwise, Counterclockwise };
inline constexpr int SHOT_ANIMATION_DISTANCE = 30;
inline constexpr std::chrono::milliseconds SHOT_ANIMATION_DURATION = std::chrono::milliseconds(100);

class TankPart {
 public:
  explicit TankPart(sf::Texture& texture);

  void rotate(const Rotation r);
  void set_rotation(const int angle);
  void draw(sf::RenderWindow& window, const float x, const float y);
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
  Tank() = delete;
  Tank(float x, float y, sf::Texture& body, sf::Texture& tower, sf::Texture& shot,
       sf::Texture& tracks, std::unique_ptr<Engine>&& engine,
       const TracesHandlerConfig& traces_handler_config = TracesHandlerConfig{});
  Tank(const Tank&);
  Tank(Tank&&);
  Tank& operator=(const Tank&);
  Tank& operator=(Tank&&);
  ~Tank() = default;

  void rotate_body(Rotation r);
  void rotate_tower(Rotation r);
  void set_rotation(const int angle);

  void set_gear(Gear gear);
  void draw(sf::RenderWindow& draw);
  void update();
  void shot();

  float get_tower_rotation() const;
  sf::Vector2f get_position();
  float get_current_speed();

 private:
  inline constexpr static float M_SPEED = 0.01f;
  void update_shot();
  void update_position();
  void draw_shot(sf::RenderWindow& draw);
  void draw_tracks(sf::RenderWindow& draw);

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
