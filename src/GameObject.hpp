#pragma once
#include <SFML/Graphics.hpp>

struct GameObject {
  virtual sf::Vector2f get_pos() const = 0;
  virtual float get_radius() const = 0;
  virtual ~GameObject() = default;
};