#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <deque>

class TracesHandler {
  sf::Texture& mTracks;
  std::deque<sf::Sprite> mTraces{};
  sf::Sprite& mTankSprite;
  sf::Vector2f mLastTankPos{};

 public:
  TracesHandler(sf::Texture& tracks, sf::Sprite& tankSprite);
  void update();
  const std::deque<sf::Sprite>& getTraces();
};
