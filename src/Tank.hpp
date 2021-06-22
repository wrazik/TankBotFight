#pragma once

#include "TextureStore.hpp"
#include <SFML/Graphics.hpp>

enum class Rotation
{
  None,
  Clockwise,
  Counterclockwise
};

class TankPart
{
public:
  TankPart(sf::Texture& texture);

  void rotate(const Rotation r);
  void set_rotation(const int angle);
  void draw(sf::RenderWindow& window, const float x, const float y);
  float get_rotation() const;

private:
  void update();
  sf::Sprite mSprite;
  Rotation mRotation = Rotation::None;
};

class Tank
{
public:
  Tank(float x, float y, sf::Texture& body, sf::Texture& tower);

  void rotate_body(Rotation r);
  void rotate_tower(Rotation r);

  void draw(sf::RenderWindow& draw);
  void set_current_speed(float speed);

private:
  void update();
  inline constexpr static float M_SPEED = 0.01f;

  sf::Vector2f mPos;
  float mCurrentSpeed = 0.0f;

  TankPart mBody;
  TankPart mTower;
};
