#include "SquareRootEngine.hpp"

#include <cmath>
#include <iostream>

#include "Size.hpp"

float to_radians(float);
SquareRootEngine::SquareRootEngine(int step_count) : mStepCount(step_count) {}

void SquareRootEngine::set_gear(Gear gear) {
  if (mCurrentGear == Gear::Neutral && gear != Gear::Neutral) {
    mStep = get_step_for_current_speed();
  }
  std::cout << mStep << '\n';
  mCurrentGear = gear;
}

int SquareRootEngine::get_step_for_current_speed() {
  if (mCurrentSpeed == 0) {
    return 1;
  }
  return std::pow(mCurrentSpeed * std::sqrt(mStepCount) / mMaxSpeed, 2);
}

void SquareRootEngine::set_speed(float speed) {
  // dryfowanie
  // zmiana stanu
  if (mMaxSpeed == 0 && speed != 0) {
    mChangeState = true;
    mFreeride = false;
  }
  if (mMaxSpeed != 0 && speed == 0) {
    std::cout << mStep << '\n';
    // mStep = mStepCount - mStep;
    mChangeState = true;
    mFreeride = true;
    std::cout << mStepCount << '\n';
    std::cout << mStep << '\n';
  } else {
    // brake = false;
  }
  // hamowanie / cofanie
  if (speed < 0) {
  }
  // przyspieszanie / jechanie
  if (speed > 0) {
  }
  mMaxSpeed = speed;
}

float SquareRootEngine::get_current_speed() const { return mCurrentSpeed; }

void SquareRootEngine::update() {
  mBrake = update_brake();
  update_current_speed();
  update_step();
}

bool SquareRootEngine::update_brake() {
  if (mCurrentGear == Gear::Reverse && mCurrentSpeed > 0) {
    return true;
  }
  if (mCurrentGear == Gear::Drive && mCurrentSpeed < 0) {
    return true;
  }
  return false;
}

void SquareRootEngine::update_step() {
  
  if (mCurrentSpeed == 0) {
    mStep = 1;
  }
  // std::cout << mStep << '\n';
  if (mStep < mStepCount) {
    mStep++;
  }
  // if (mMaxSpeed == 0) {
  //   mStep--;
  // }
}

void SquareRootEngine::update_current_speed() {
  // gdy gracz przyspiesza to powinien przyspieszac pierwiastkowo [OK]
  // gdy gracz puszcza przyspieszczenie to powinien 'dryfowac', zwalniajac pierwiastkowo [OK]
  // gdy gracz znowu chce przyspieszac, to powinien przyspieszac z aktualnej predkosci [FAIL]
  // gdy gracz przyspieszajac, nagle stwierdza ze chce sie cofac to powinien najpierw hamowac
  // (szybciej zwalniac), a potem dopiero sie cofac z funkcja pierwiastkowa [FAIL]

  // check if speed is not out of bounds
  if (mBrake) {
    std::cout << "BRAKES!\n";
    if (mCurrentSpeed < 0) {
      mCurrentSpeed += 3 * freeride();
      mCurrentSpeed = mCurrentSpeed > 0 ? 0 : mCurrentSpeed;
    }
    if (mCurrentSpeed > 0) {
      mCurrentSpeed -= 3 * freeride();
      mCurrentSpeed = mCurrentSpeed < 0 ? 0 : mCurrentSpeed;
    }
  } else if (mCurrentGear == Gear::Neutral) {
    if (mCurrentSpeed < 0) {
      mCurrentSpeed += freeride();
      mCurrentSpeed = mCurrentSpeed > 0 ? 0 : mCurrentSpeed;
    }
    if (mCurrentSpeed > 0) {
      mCurrentSpeed -= freeride();
      mCurrentSpeed = mCurrentSpeed < 0 ? 0 : mCurrentSpeed;
    }
    // mStep--;
    // std::cout << "speed " << mCurrentSpeed << "\n";
  } else if (mCurrentGear == Gear::Drive) {
    if (mCurrentSpeed < mMaxSpeed) {
      mCurrentSpeed += get_speed_delta();
    }
    // mStep++;
  } else if (mCurrentGear == Gear::Reverse) {
    mCurrentSpeed -= get_speed_delta();
  }
  // if (mMaxSpeed != 0) {
  //   brake = false;
  // // }
  // if (mStep < mStepCount && mStep > 0) {
  //   // mStep++;
  // }
}

float SquareRootEngine::accelerate() {
  return mMaxSpeed * (std::sqrt(mStep) / std::sqrt(mStepCount));
}

float SquareRootEngine::get_speed_delta() {
  return mMaxSpeed * (std::sqrt(mStep) / std::sqrt(mStepCount)) - std::abs(mCurrentSpeed);
}

float SquareRootEngine::freeride() { return mMaxSpeed / mStepCount; }

sf::Vector2f SquareRootEngine::get_position_delta(float rotation_radians) {
  mPositionDelta.x = mCurrentSpeed * std::cos(rotation_radians - pi / 2);
  mPositionDelta.y = mCurrentSpeed * std::sin(rotation_radians - pi / 2);
  return mPositionDelta;
}
