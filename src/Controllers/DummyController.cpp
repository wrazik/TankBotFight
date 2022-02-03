#include "DummyController.hpp"

#include <Board.hpp>
#include <Random.hpp>
#include <Tank.hpp>
#include <iostream>

DummyController::DummyController(const std::shared_ptr<Tank> &tank, Board &board)
    : mTank(tank), mBoard(board) {
  mLastChange = std::chrono::system_clock::now();
}

void DummyController::update() {
  if (mTank.expired()) {
    return;
  }
  const auto &tank = mTank.lock();
  const auto now = std::chrono::system_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastChange);

  constexpr auto SWITCH_INTERVAL = std::chrono::milliseconds{200};
  if (elapsed > SWITCH_INTERVAL || mCurrentMove == DummyMove::Shot) {
    mCurrentMove = one_of(DummyMove::Forward, DummyMove::Idle, DummyMove::Shot, DummyMove::TurnLeft,
                          DummyMove::TurnRight);
    mLastChange = now;
  }

  switch (mCurrentMove) {
    case DummyMove::Shot:
      mBoard.fire_missle(*tank);
      break;
    case DummyMove::Forward:
      tank->set_gear(Gear::Drive);
      break;
    case DummyMove::TurnLeft:
      tank->rotate_body(Rotation::Clockwise);
      tank->rotate_tower(Rotation::Clockwise);
      break;
    case DummyMove::TurnRight:
      tank->rotate_body(Rotation::Counterclockwise);
      tank->rotate_tower(Rotation::Counterclockwise);
      break;
    case DummyMove::Idle:
      tank->set_gear(Gear::Neutral);
      break;
    default:
      break;
  }
}
