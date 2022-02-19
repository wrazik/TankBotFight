#include "DummyController.hpp"

#include <Board.hpp>
#include <Random.hpp>
#include <Tank/Tank.hpp>
#include <iostream>

DummyController::DummyController(Tank &tank, Board &board) : mTank(tank), mBoard(board) {
  mLastChange = std::chrono::system_clock::now();
}

void DummyController::update() {
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
      if (const auto &missile = mTank.shoot()) {
        mBoard.register_missile(missile.value());
      }
      break;
    case DummyMove::Forward:
      mTank.set_gear(Gear::Drive);
      break;
    case DummyMove::TurnLeft:
      mTank.rotate_body(Rotation::Clockwise);
      mTank.rotate_tower(Rotation::Clockwise);
      break;
    case DummyMove::TurnRight:
      mTank.rotate_body(Rotation::Counterclockwise);
      mTank.rotate_tower(Rotation::Counterclockwise);
      break;
    case DummyMove::Idle:
      mTank.set_gear(Gear::Neutral);
      break;
    default:
      break;
  }
}
