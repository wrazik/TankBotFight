#pragma once

#include "Engine.hpp"

class SquareRootEngine : public Engine {
 public:
  SquareRootEngine(const int step_count, const int max_speed);
  void set_gear(const Gear gear) override;
  float get_current_speed() const override;
  sf::Vector2f get_position_delta(const float rotation_radians) override;
  void update() override;
  std::unique_ptr<Engine> copy() const override;
  ~SquareRootEngine() = default;

 private:
  float calculate_current_speed() const;
  int calculate_step() const;
  bool is_braking() const;
  int get_step_for_current_speed() const;
  float get_speed_delta() const;
  float freeride() const;
  float reduce_abs_speed_by(const float) const;

  Gear mCurrentGear{Gear::Neutral};
  float mCurrentSpeed{};
  float mMaxSpeed{5};
  int mStep{0};
  int mStepCount{};
  sf::Vector2f mPositionDelta{};
  bool mBrake{false};
};
