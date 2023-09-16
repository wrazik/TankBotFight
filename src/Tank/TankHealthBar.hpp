#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

class TankHealthBar {
 public:
  explicit TankHealthBar(unsigned int total_health);

  void set_position(const sf::Vector2f& pos);
  void set_health(unsigned int health);
  void draw(sf::RenderWindow& window);

 private:
  void setup_text();
  void setup_bar();
  void update_string();
  void update_health_size();

  unsigned int mHealth;
  unsigned int mTotalHealth;
  sf::Font mFont;
  sf::Text mText;
  sf::RectangleShape mBarShape;
  sf::RectangleShape mHealthShape;
};
