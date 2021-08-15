#include "SquareRootEngine.hpp"

#include <cmath>

#include "Size.hpp"

SquareRootEngine::SquareRootEngine(int step_count) : mStepCount(step_count) {}

void SquareRootEngine::set_speed(float speed) {
  mMaxSpeed = speed;
  if (speed == 0) {
    mStep = 1;
  }
}

float SquareRootEngine::get_current_speed() const { return mCurrentSpeed; }

void SquareRootEngine::update() { update_current_speed(); }

void SquareRootEngine::update_current_speed() {
  if (mStep > mStepCount) {
    return;
  }
  mCurrentSpeed = mMaxSpeed * (std::sqrt(mStep) / std::sqrt(mStepCount));
  if (mMaxSpeed != 0) {
    mStep++;
  }
}

sf::Vector2f SquareRootEngine::get_position_delta(float rotation_radians) {
  mPositionDelta.x = mCurrentSpeed * std::cos(rotation_radians - pi/2);
  mPositionDelta.y = mCurrentSpeed * std::sin(rotation_radians - pi/2);
  return mPositionDelta;
}
