#pragma once

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
  void update_string();

  unsigned int mHealth;
  unsigned int mTotalHealth;
  sf::Font mFont;
  sf::Text mText;
};
