#pragma once
#include <chrono>
#include <memory>

#include "Tank.hpp"

class Board;
namespace sf {
class Event;
}

class KeyboardController {
 public:
  KeyboardController(const std::shared_ptr<Tank>& tank, Board& board);
  void update(const sf::Event& event);

 private:
  void handle_shot();
  std::weak_ptr<Tank> mTank;
  Board& mBoard;
  std::chrono::time_point<std::chrono::system_clock> mLastShot;
};
