#pragma once
#include <chrono>
#include <memory>

#include "Tank/Tank.hpp"

class Board;
namespace sf {
class Event;
}

class KeyboardController {
 public:
  KeyboardController(const std::shared_ptr<Tank>& tank, Board& board);
  void update(const sf::Event& event);

 private:
  std::weak_ptr<Tank> mTank;
  Board& mBoard;
};
