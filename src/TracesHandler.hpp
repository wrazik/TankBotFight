#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

class TracesHandler {
  sf::Texture& mTracks;
  std::deque<sf::Sprite> mTraces{};
  sf::Vector2f mStartingPosition{};

 public:
  TracesHandler(sf::Texture& tracks, const sf::Vector2f& pos);
  void update(const sf::Vector2f& move);
  const std::deque<sf::Sprite>& getTraces();
};
