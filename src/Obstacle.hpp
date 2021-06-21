#pragma once

#include <SFML/Graphics.hpp>

class Obstacle
{

public:
  Obstacle(int x, int y);

  sf::Sprite getSprite();

private:
  sf::Texture txt;
  sf::Sprite sprite;
};
