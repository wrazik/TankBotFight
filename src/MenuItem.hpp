#pragma once

#include <SFML/Graphics.hpp>

class MenuItem {
 protected:
  sf::Vector2f mPosition;

 public:
  MenuItem(sf::Vector2f position);
};