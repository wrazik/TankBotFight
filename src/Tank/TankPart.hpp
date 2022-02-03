#pragma once

#include <SFML/Graphics.hpp>

enum class Rotation { None, Clockwise, Counterclockwise };

class TankPart {
 public:
  explicit TankPart(sf::Texture& texture);

  void rotate(Rotation r);
  void set_rotation(float angle);
  void draw(sf::RenderWindow& window);
  float get_rotation() const;
  sf::Sprite& get_sprite();
  const sf::Sprite& get_sprite() const;
  void update();

 private:
  sf::Sprite mSprite;
  Rotation mRotation = Rotation::None;
};
