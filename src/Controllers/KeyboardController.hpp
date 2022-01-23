#pragma once
#include <chrono>

#include "IController.hpp"

class Tank;
class Board;
namespace sf {
class Event;
}

class KeyboardController : public IController {
 public:
  KeyboardController(Tank& tank, Board& board);
  void update(const sf::Event& event) override;

 private:
  void handle_shot();
  Tank& mTank;
  Board& mBoard;
  std::chrono::time_point<std::chrono::system_clock> mLastShot;
};
