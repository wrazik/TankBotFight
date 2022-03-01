#pragma once

class Board;
class Tank;
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
};
