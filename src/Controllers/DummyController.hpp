#pragma once
#include <chrono>

#include "IController.hpp"

class Tank;
class Board;

enum class DummyMove {
  Forward,
  TurnLeft,
  TurnRight,
  Backward,
  Shot,
};

class DummyController : public IController {
 public:
  DummyController(Tank& tank, Board& board);
  void update(const sf::Event& event) override;

 private:
  Tank& mTank;
  Board& mBoard;
  DummyMove mCurrentMove = DummyMove::Forward;
  std::chrono::time_point<std::chrono::system_clock> mLastChange;
};