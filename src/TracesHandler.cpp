#include "TracesHandler.hpp"

#include "utility.hpp"
constexpr int tracesCount = 70;

void setSpriteTextureHeight(sf::Sprite& sprite, int amount) {
  const auto& rect = sprite.getTextureRect();
  sprite.setTextureRect({rect.left, rect.top, rect.width, amount});
}

void increaseSpriteHeight(sf::Sprite& sprite, const int amount) {
  const auto& rect = sprite.getTextureRect();
  setSpriteTextureHeight(sprite, rect.height + amount);
}

sf::Vector2f getMiddleTopTransform(const sf::Sprite& sprite, const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({width / 2, 0.f + additional_value});
}

sf::Vector2f getMiddleBotTransform(const sf::Sprite& sprite, const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({width / 2, height + additional_value});
}

bool TracesHandler::is_move_zero() const { return equal(mTankSprite.getPosition(), mLastTankPos); }

TracesHandler::TracesHandler(const sf::Texture& texture, sf::Sprite& tankSprite,
                             const sf::Vector2f& startingPosition)
    : mTracksTexture(texture),
      mTankSprite(tankSprite),
      mLastTankPos(startingPosition),
      mMaxTextureHeight(mTracksTexture.getSize().y - 4) {}

int TracesHandler::get_texture_height(const float move_distance) {
  mTextureHeight += move_distance;
  int return_value = static_cast<int>(mTextureHeight);
  mTextureHeight -= return_value;
  return return_value;
}

bool TracesHandler::is_moving_forward(const sf::Vector2f& move) const {
  return equal(get_angle(move), mTankSprite.getRotation(), 1.0);
}

void TracesHandler::update() {
  if (is_move_zero()) {
    mLastTankPos = mTankSprite.getPosition();
    return;
  }
  // print_point(move);
  // if (mTraces.size() > tracesCount) {
  //   mTraces.pop_front();
  // }
  const auto& move = mTankSprite.getPosition() - mLastTankPos;
  mLastTankPos = mTankSprite.getPosition();
  const float moveDistance = hypot(move);
  int texture_height = get_texture_height(moveDistance);
  sf::Sprite sprite(mTracksTexture);
  const auto& rect = sprite.getTextureRect();
  sprite.setOrigin(rect.width / 2, 0);
  float moveAngle = get_angle(move) - 180.f;
  if (moveAngle < 0.f) {
    moveAngle = 360.f + moveAngle;
  }
  sprite.setRotation(moveAngle);
  // this depends whether tank moves forward or backward
  std::cout << "body rotation: " << mTankSprite.getRotation() << "\n";
  std::cout << "move angle: " << get_angle(move) << "\n";
  if (is_moving_forward(move)) {
    sprite.setPosition(getMiddleBotTransform(mTankSprite, moveDistance));
  } else {
    std::cout << "is not moving forward\n";
    sprite.setPosition(getMiddleTopTransform(mTankSprite, -moveDistance));
  }
  std::cout << "-------------------\n";
  setSpriteTextureHeight(sprite, texture_height);
  // default; should be done if none of the conditions is true!
  // the same angle; increase the sprite height accordingly
  if (!mTraces.empty() && equal(mTraces.back().getRotation(), moveAngle, 1.0)) {
    // std::cout << "the same angle\n";
    sf::Sprite& trace = mTraces.back();
    const auto traceRect = trace.getTextureRect();
    // if current move distance would overrun max texture height
    if (texture_height + traceRect.height > mMaxTextureHeight) {
      int newTrackHeight = texture_height - (mMaxTextureHeight - traceRect.height);
      setSpriteTextureHeight(trace, mMaxTextureHeight);
      setSpriteTextureHeight(sprite, newTrackHeight);
      if (is_moving_forward(move)) {
        sprite.setPosition(getMiddleBotTransform(mTankSprite, newTrackHeight));
      } else {
        sprite.setPosition(getMiddleTopTransform(mTankSprite, -newTrackHeight));
      }
    } else {
      increaseSpriteHeight(trace, texture_height);
      DISTANCE_TRAVELLED += moveDistance;
      TOTAL_TEXTURE_HEIGHT += texture_height;
      // std::cout << "total distance: " << DISTANCE_TRAVELLED << "\n";
      // std::cout << "texture height: " << TOTAL_TEXTURE_HEIGHT << "\n";
      // std::cout << "----------------------------------\n";
      return;
    }
  }
  mTraces.push_back(sprite);
}

const std::deque<sf::Sprite>& TracesHandler::getTraces() const { return mTraces; }
