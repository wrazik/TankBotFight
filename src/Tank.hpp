#pragma once

#include <SFML/Graphics.hpp>

enum class Direction;

class Tank
{

public:
  Tank(int x, int y, float speed);

  void move(Direction direction);

  void dead();

  sf::Sprite& getSprite();

private:
  int mHp = 100;
  float mSpeed = 0.f;

  sf::Texture txt;
  sf::Sprite sprite;
};
