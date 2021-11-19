#pragma once

#include <SFML/Graphics.hpp>

class Obstacle {
 public:
  Obstacle(int x, int y);

  sf::Sprite get_sprite();

 private:
  sf::Texture mTxt;
  sf::Sprite mSprite;
};
