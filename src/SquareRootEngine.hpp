#pragma once

#include "Engine.hpp"

class SquareRootEngine : public Engine {
 public:
  explicit SquareRootEngine(int step_count);
  void set_speed(float speed) override;
  float get_current_speed() const override;
  sf::Vector2f get_position_delta(float rotation_radians) override;
  void update() override;
  ~SquareRootEngine() = default;

 private:
  void update_current_speed();

  float mCurrentSpeed{};
  float mMaxSpeed{};
  int mStep{1};
  int mStepCount{};
  sf::Vector2f mPositionDelta{};
};
