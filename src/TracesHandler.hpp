#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

#include "Trace.hpp"

struct TracesHandlerConfig {
  int mMaxTraceAge{50};
  float mDecayRate{0.1f};
};

class TracesHandler {
  const sf::Texture& mTracksTexture;
  sf::Sprite& mTankSprite;
  std::deque<Trace> mTraces;
  std::deque<short> mTracesAge;
  sf::Vector2f mLastTankPos;
  int mMaxTextureHeight{};
  TracesHandlerConfig mConfig{};

  void update_traces_age();
  void decay_traces();
  void add_trace(const Trace& trace);
  void remove_trace();
  bool is_move_angle_changed(const sf::Vector2f& move) const;
  Trace make_trace(const sf::Vector2f& move) const;
  bool is_moving_forward(const sf::Vector2f& move) const;

 public:
  TracesHandler(const sf::Texture& tracks, sf::Sprite& tank_sprite, const sf::Vector2f& start_pos,
                int max_trace_age, float decay_rate);
  TracesHandler(const sf::Texture& tracks, sf::Sprite& tank_sprite, const sf::Vector2f& start_pos,
                const TracesHandlerConfig& config = TracesHandlerConfig{});
  TracesHandler(const TracesHandler&) = delete;
  TracesHandler(TracesHandler&&) noexcept = delete;
  TracesHandler& operator=(const TracesHandler&) = delete;
  TracesHandler& operator=(TracesHandler&&) noexcept = delete;
  ~TracesHandler() = default;

  [[nodiscard]] const std::deque<Trace>& get_traces() const;
  [[nodiscard]] const sf::Texture& get_trace_texture() const;
  [[nodiscard]] TracesHandlerConfig get_config() const;
  void update();
};
