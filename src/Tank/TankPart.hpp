#pragma once

#include <SFML/Graphics.hpp>

enum class Rotation { None, Clockwise, Counterclockwise };

class TankPart {
 public:
  explicit TankPart(sf::Texture& texture);

  void rotate(Rotation r);
  void set_rotation(float angle);
  void draw(sf::RenderWindow& window);
  void update();

  [[nodiscard]] float get_rotation() const;
  [[nodiscard]] sf::Sprite& get_sprite();
  [[nodiscard]] const sf::Sprite& get_sprite() const;

 private:
  sf::Sprite mSprite;
  Rotation mRotation = Rotation::None;
};
