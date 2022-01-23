#include "DummyController.hpp"

#include <Board.hpp>
#include <Random.hpp>
#include <Tank.hpp>
#include <iostream>

DummyController::DummyController(Tank &tank, Board &board) : mTank(tank), mBoard(board) {
  mLastChange = std::chrono::system_clock::now();
}

void DummyController::update(const sf::Event &) {
  const auto now = std::chrono::system_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastChange);

  constexpr auto SWITCH_INTERVAL = std::chrono::seconds{0};
  if (elapsed > SWITCH_INTERVAL || mCurrentMove == DummyMove::Shot) {
    mCurrentMove = one_of(DummyMove::Forward, DummyMove::Backward, DummyMove::Shot,
                          DummyMove::TurnLeft, DummyMove::TurnRight);
    mLastChange = now;
  }

  switch (mCurrentMove) {
    case DummyMove::Shot:
      mBoard.fire_missle(mTank);
      break;
    case DummyMove::Forward:
      mTank.set_gear(Gear::Drive);
      break;
    case DummyMove::Backward:
      mTank.set_gear(Gear::Reverse);
      break;
    case DummyMove::TurnLeft:
      mTank.rotate_body(Rotation::Clockwise);
      mTank.rotate_tower(Rotation::Clockwise);
      break;
    case DummyMove::TurnRight:
      mTank.rotate_body(Rotation::Counterclockwise);
      mTank.rotate_tower(Rotation::Counterclockwise);
      break;
    default:
      break;
  }
}