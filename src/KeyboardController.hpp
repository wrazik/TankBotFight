#pragma once
#include <chrono>

class Tank;
class Board;
namespace sf {
class Event;
}

class KeyboardController {
 public:
  KeyboardController(Tank& tank, Board& board);
  void update(const sf::Event& event);

 private:
  Tank& mTank;
  Board& mBoard;
  std::chrono::milliseconds mLastDelay{0};
  std::chrono::time_point<std::chrono::system_clock> mLastShot;
};
