#pragma once
#include <SFML/Graphics.hpp>

class Missle {
 public:
  Missle(sf::Texture& texture, float angle, float x, float y);
  void draw(sf::RenderWindow& window);
  void update();
  sf::Vector2f get_pos() const;

 private:
  sf::Sprite mSprite;
  float mSpeed = 20.0f;

  sf::Vector2f mPos;
  float mAngle;
};
