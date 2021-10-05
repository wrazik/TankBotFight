#include "TracesHandler.hpp"

#include "utility.hpp"
constexpr int tracesCount = 1;

void increaseSpriteHeight(sf::Sprite& sprite, int amount) {
  const auto& rect = sprite.getTextureRect();
  sprite.setTextureRect({rect.top, rect.left, rect.width, rect.height + amount});
}

TracesHandler::TracesHandler(sf::Texture& texture, const sf::Vector2f& pos)
    : mTracks(texture), mStartingPosition(pos) {}

void TracesHandler::update(const sf::Vector2f& move) {
  sf::Sprite sprite(mTracks);
  const auto& rect = sprite.getTextureRect();
  const float moveAngle = get_angle(move);
  if (!mTraces.empty() && mTraces.back().getRotation() == moveAngle) {
    auto& trace = mTraces.back();
    increaseSpriteHeight(trace, hypot(move));
  } else {
    sprite.setTextureRect({rect.top, rect.left, rect.width, static_cast<int>(hypot(move))});
    sprite.setRotation(moveAngle);
    mTraces.push_back(sprite);
  }
}

const std::deque<sf::Sprite>& TracesHandler::getTraces() { return mTraces; }
