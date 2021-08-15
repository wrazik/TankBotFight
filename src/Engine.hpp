#pragma once
#include <SFML/System/Vector2.hpp>

class Engine {
 public:
  virtual void set_speed(float speed) = 0;
  virtual float get_current_speed() const = 0;
  virtual sf::Vector2f get_position_delta(float rotation_radians) = 0;
  virtual void update() = 0;
  virtual ~Engine() = default;
};
