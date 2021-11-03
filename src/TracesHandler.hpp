#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

class TracesHandler {
  const sf::Texture& mTracksTexture;
  sf::Sprite& mTankSprite;
  std::deque<sf::Sprite> mTraces{};
  sf::Vector2f mLastTankPos{};
  float mMaxTextureHeight{};
  float mTextureHeight{};

  bool is_move_zero() const;
  int get_current_move_texture_height(const float);
  bool is_move_angle_changed(const sf::Vector2f& move) const;
  float get_opposite_angle(const sf::Vector2f& move) const;
  sf::Sprite get_sprite(const sf::Vector2f& move, const int sprite_height) const;
  bool is_moving_forward(const sf::Vector2f&) const;
  bool new_height_exceeds_max_height(const int sprite_height) const;
  int get_new_trace_height(const int sprite_height) const;

 public:
  TracesHandler(const sf::Texture& tracks, sf::Sprite& tankSprite,
                const sf::Vector2f& startingPosition);
  TracesHandler(const TracesHandler&) = delete;
  TracesHandler(TracesHandler&&) = delete;
  TracesHandler& operator=(const TracesHandler&) = delete;
  TracesHandler& operator=(TracesHandler&&) = delete;
  ~TracesHandler() = default;

  const std::deque<sf::Sprite>& get_traces() const;
  float get_max_texture_height() const;
  void update();
};
