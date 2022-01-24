#pragma once
#include <chrono>

class Tank;
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
  DummyController(Tank& tank, Board& board);
  void update();

 private:
  Tank& mTank;
  Board& mBoard;
  DummyMove mCurrentMove = DummyMove::Idle;
  std::chrono::time_point<std::chrono::system_clock> mLastChange;
};