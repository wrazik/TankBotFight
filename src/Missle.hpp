#pragma once
#include <SFML/Graphics.hpp>

#include "MovementState.hpp"
class Missle {
 public:
  Missle(sf::Texture& texture, const MovementState& state);
  void draw(sf::RenderWindow& window);
  void update();
  [[nodiscard]] sf::Vector2f get_pos() const;

 private:
  sf::Sprite mSprite;
  float mSpeed = 20.0f;

  sf::Vector2f mPos;
  float mAngle;
};
