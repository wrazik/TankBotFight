#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>

enum class Gear { Drive, Neutral, Reverse };
class Engine {
 public:
  virtual void set_gear(Gear) = 0;
  [[nodiscard]] virtual float get_current_speed() const = 0;
  [[nodiscard]] virtual sf::Vector2f get_position_delta(float rotation_radians) = 0;
  virtual void update() = 0;
  [[nodiscard]] virtual std::unique_ptr<Engine> copy() const = 0;
  virtual ~Engine() = default;
};
