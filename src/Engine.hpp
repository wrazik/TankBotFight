#pragma once
#include <SFML/System/Vector2.hpp>

enum class Gear { Drive, Neutral, Reverse };
class Engine {
 public:
  virtual void set_gear(Gear) = 0;
  virtual float get_current_speed() const = 0;
  virtual sf::Vector2f get_position_delta(float rotation_radians) = 0;
  virtual void update() = 0;
  virtual ~Engine() = default;
};
