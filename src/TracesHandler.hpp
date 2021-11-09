#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

#include "Trace.hpp"

class TracesHandler {
  const sf::Texture& mTracksTexture;
  sf::Sprite& mTankSprite;
  std::deque<Trace> mTraces{};
  std::deque<short> mTracesAge{};
  sf::Vector2f mLastTankPos{};
  int mMaxTextureHeight{};
  int mMaxTraceAge{};
  float mTraceDecayRate{};

  void update_traces_age();
  void decay_traces();
  void add_trace(const Trace& sp);
  void remove_trace();
  bool is_move_angle_changed(const sf::Vector2f& move) const;
  float get_opposite_angle(const float angle) const;
  Trace make_trace(const sf::Vector2f& move) const;
  bool is_moving_forward(const sf::Vector2f&) const;

 public:
  TracesHandler(const sf::Texture& tracks, sf::Sprite& tank_sprite, const sf::Vector2f& start_pos,
                const int max_trace_age, const float decay_rate);
  TracesHandler(const TracesHandler&) = delete;
  TracesHandler(TracesHandler&&) = delete;
  TracesHandler& operator=(const TracesHandler&) = delete;
  TracesHandler& operator=(TracesHandler&&) = delete;
  ~TracesHandler() = default;

  std::deque<Trace> get_traces() const;
  float get_max_texture_height() const;
  const sf::Texture& get_trace_texture() const;
  int get_max_trace_age() const;
  float get_trace_decay_rate() const;
  void update();
};
