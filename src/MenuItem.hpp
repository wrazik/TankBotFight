#pragma once

#include <SFML/Graphics.hpp>

class MenuItem {
 public:
  MenuItem(sf::Vector2f position);

 protected:
  sf::Vector2f mPosition;
};