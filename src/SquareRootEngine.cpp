#include "SquareRootEngine.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "Size.hpp"
#include "utility.hpp"

SquareRootEngine::SquareRootEngine(int step_count, int max_speed)
    : mStepCount(step_count), mMaxSpeed(max_speed) {}

std::unique_ptr<Engine> SquareRootEngine::copy() const {
  return std::make_unique<SquareRootEngine>(mStepCount, mMaxSpeed);
}

void SquareRootEngine::set_gear(Gear gear) {
  if (mCurrentGear == Gear::Neutral && gear != Gear::Neutral) {
    mStep = get_step_for_current_speed();
  }
  mCurrentGear = gear;
}

int SquareRootEngine::get_step_for_current_speed() const {
  if (mCurrentSpeed == 0) {
    return 1;
  }
  return std::pow(mCurrentSpeed * std::sqrt(mStepCount) / mMaxSpeed, 2);
}

float SquareRootEngine::get_current_speed() const { return mCurrentSpeed; }

void SquareRootEngine::update() {
  mBrake = update_brake();
  mCurrentSpeed = update_current_speed();
  mStep = update_step();
}

bool SquareRootEngine::update_brake() const {
  if (mCurrentGear == Gear::Reverse && mCurrentSpeed > 0) {
    return true;
  }
  if (mCurrentGear == Gear::Drive && mCurrentSpeed < 0) {
    return true;
  }
  return false;
}

int SquareRootEngine::update_step() const {
  if (mCurrentSpeed == 0) {
    return 1;
  }
  if (mStep < mStepCount) {
    return mStep + 1;
  }
  return mStep;
}

float SquareRootEngine::update_current_speed() const {
  if (mBrake) {
    return reduce_abs_speed_by(3 * freeride());
  } else if (mCurrentGear == Gear::Neutral) {
    return reduce_abs_speed_by(freeride());
  } else if (mCurrentGear == Gear::Drive) {
    return mCurrentSpeed + get_speed_delta();
  } else if (mCurrentGear == Gear::Reverse) {
    return mCurrentSpeed - get_speed_delta();
  }
  throw std::logic_error("unexpected exception; gear is other than {neutral, drive, reverse}");
}

float SquareRootEngine::reduce_abs_speed_by(float amount) const {
  if (mCurrentSpeed < 0) {
    return std::min(mCurrentSpeed + amount, 0.f);
  }
  if (mCurrentSpeed > 0) {
    return std::max(mCurrentSpeed - amount, 0.f);
  }
  return mCurrentSpeed;
}

float SquareRootEngine::get_speed_delta() const {
  return mMaxSpeed * (std::sqrt(mStep) / std::sqrt(mStepCount)) - std::abs(mCurrentSpeed);
}

float SquareRootEngine::freeride() const { return mMaxSpeed / mStepCount; }

sf::Vector2f SquareRootEngine::get_position_delta(float rotation_radians) {
  mPositionDelta.x = mCurrentSpeed * std::cos(rotation_radians - pi / 2);
  mPositionDelta.y = mCurrentSpeed * std::sin(rotation_radians - pi / 2);
  return mPositionDelta;
}
