#pragma once

namespace sf {
class Event;
}

class IController {
 public:
  virtual void update(const sf::Event& event) = 0;
  virtual ~IController() = default;
};