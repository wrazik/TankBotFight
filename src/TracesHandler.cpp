#include "TracesHandler.hpp"

#include "utility.hpp"
constexpr int tracesCount = 1;

void increaseSpriteHeight(sf::Sprite& sprite, int amount) {
  const auto& rect = sprite.getTextureRect();
  sprite.setTextureRect({rect.top, rect.left, rect.width, rect.height + amount});
}

sf::Vector2f getMiddleBotTransform(const sf::Sprite& sprite) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({left + width / 2, top + height});
}

TracesHandler::TracesHandler(sf::Texture& texture, sf::Sprite& tankSprite)
    : mTracks(texture), mTankSprite(tankSprite), mLastTankPos(mTankSprite.getPosition()) {}

void TracesHandler::update() {
  const auto& move = mTankSprite.getPosition() - mLastTankPos;
  mLastTankPos = mTankSprite.getPosition();
  sf::Sprite sprite(mTracks);
  const auto& rect = sprite.getTextureRect();
  sprite.setOrigin(rect.width / 2, 0.f);
  const float moveAngle = get_angle(move);
  if (!mTraces.empty() && mTraces.back().getRotation() == moveAngle) {
    auto& trace = mTraces.back();
    increaseSpriteHeight(trace, hypot(move));
  } else {
    sprite.setTextureRect({rect.top, rect.left, rect.width, static_cast<int>(hypot(move))});
    sprite.setRotation(moveAngle);
    sprite.setPosition(getMiddleBotTransform(mTankSprite));
    mTraces.push_back(sprite);
  }
}

const std::deque<sf::Sprite>& TracesHandler::getTraces() { return mTraces; }
