#pragma once

#include "Engine.hpp"

class SquareRootEngine : public Engine {
 public:
  SquareRootEngine(int step_count, int max_speed);
  void set_gear(Gear gear) override;
  float get_current_speed() const override;
  sf::Vector2f get_position_delta(float rotation_radians) override;
  void update() override;
  std::unique_ptr<Engine> copy() const;
  ~SquareRootEngine() = default;

 private:
  float update_current_speed() const;
  int update_step() const;
  bool update_brake() const;
  int get_step_for_current_speed() const;
  float get_speed_delta() const;
  float freeride() const;
  float reduce_abs_speed_by(float) const;

  Gear mCurrentGear{Gear::Neutral};
  float mCurrentSpeed{};
  float mMaxSpeed{5};
  int mStep{0};
  int mStepCount{};
  sf::Vector2f mPositionDelta{};
  bool mBrake{false};
};
