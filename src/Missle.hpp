#pragma once
#include <SFML/Graphics.hpp>

#include "MovementState.hpp"
class Missle {
 public:
  Missle(sf::Texture& texture, const MovementState& state, unsigned int damage);
  void draw(sf::RenderWindow& window);
  void update();
  [[nodiscard]] sf::Vector2f get_pos() const;
  [[nodiscard]] unsigned int get_damage() const;

  bool operator==(const Missle& rhs) const;

 private:
  sf::Sprite mSprite;
  float mSpeed = 20.0f;
  unsigned int mDamage;

  sf::Vector2f mPos;
  float mAngle;
};
