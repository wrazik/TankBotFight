#pragma once
#include <chrono>
#include <memory>

#include "Tank.hpp"

class Board;

enum class DummyMove {
  Forward,
  TurnLeft,
  TurnRight,
  Shot,
  Idle,
};

class DummyController {
 public:
  DummyController(const std::shared_ptr<Tank>& tank, Board& board);
  void update();

 private:
  std::weak_ptr<Tank> mTank;
  Board& mBoard;
  DummyMove mCurrentMove = DummyMove::Idle;
  std::chrono::time_point<std::chrono::system_clock> mLastChange;
};
