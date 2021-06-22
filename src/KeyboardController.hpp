#pragma once

class Tank;
namespace sf {
class Event;
}

class KeyboardController
{
public:
  KeyboardController(Tank& tank);
  void update(const sf::Event& event);

private:
  Tank& mTank;
};
