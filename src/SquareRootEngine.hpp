#pragma once

#include "Engine.hpp"

class SquareRootEngine : public Engine {
 public:
  explicit SquareRootEngine(int step_count);
  void set_speed(float speed) override;
  void set_gear(Gear gear) override;
  float get_current_speed() const override;
  sf::Vector2f get_position_delta(float rotation_radians) override;
  void update() override;
  ~SquareRootEngine() = default;

 private:
  void update_current_speed();
  void update_step();
  bool update_brake();
  int get_step_for_current_speed();
  float accelerate();
  float get_speed_delta();
  float freeride();

  Gear mCurrentGear{Gear::Neutral};
  float mCurrentSpeed{};
  float mMaxSpeed{5};
  int mStep{0};
  int mStepCount{};
  sf::Vector2f mPositionDelta{};
  bool mBrake{false};
  bool mFreeride{false};
  bool mChangeState{false};
  float mSpeedAtChange{};
};
