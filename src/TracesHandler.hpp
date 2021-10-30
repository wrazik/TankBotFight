#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>
// #include <functional>

class TracesHandler {
  const sf::Texture& mTracksTexture;
  sf::Sprite& mTankSprite;
  std::deque<sf::Sprite> mTraces{};
  sf::Vector2f mLastTankPos{};
  float mMaxTextureHeight{};
  float DISTANCE_TRAVELLED{};
  float mTextureHeight{};
  float TOTAL_TEXTURE_HEIGHT{};

  int get_texture_height(const float);
  bool is_move_zero() const;
  bool is_moving_forward(const sf::Vector2f&) const;

 public:
  TracesHandler(const sf::Texture& tracks, sf::Sprite& tankSprite,
                const sf::Vector2f& startingPosition);
  TracesHandler(const TracesHandler&) = delete;
  TracesHandler(TracesHandler&&) = delete;
  TracesHandler& operator=(const TracesHandler&) = delete;
  TracesHandler& operator=(TracesHandler&&) = delete;
  ~TracesHandler() = default;
  void update();
  const std::deque<sf::Sprite>& getTraces() const;
  float get_max_texture_height() const;
};
