#pragma once

#include "Engine.hpp"

struct SquareRootEngineConfig {
  int mStepCount{70};
  float mMaxSpeed{5.f};
};

class SquareRootEngine : public Engine {
 public:
  explicit SquareRootEngine(const SquareRootEngineConfig& config);
  void set_gear(Gear gear) override;
  [[nodiscard]] float get_current_speed() const override;
  [[nodiscard]] sf::Vector2f get_position_delta(float rotation_radians) override;
  void update() override;
  [[nodiscard]] std::unique_ptr<Engine> copy() const override;
  ~SquareRootEngine() override = default;

 private:
  float calculate_current_speed() const;
  int calculate_step() const;
  bool is_braking() const;
  int get_step_for_current_speed() const;
  float get_speed_delta() const;
  float freeride() const;
  float reduce_abs_speed_by(float amount) const;

  Gear mCurrentGear{Gear::Neutral};
  float mCurrentSpeed{};
  float mMaxSpeed{5};
  int mStep{0};
  int mStepCount{};
  sf::Vector2f mPositionDelta{};
  bool mBrake{false};
};
