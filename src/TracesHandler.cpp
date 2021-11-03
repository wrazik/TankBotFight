#include "TracesHandler.hpp"

#include "utility.hpp"

void set_sprite_texture_height(sf::Sprite& sprite, int amount) {
  const auto& rect = sprite.getTextureRect();
  sprite.setTextureRect({rect.left, rect.top, rect.width, amount});
}

void increase_sprite_height(sf::Sprite& sprite, const int amount) {
  const auto& rect = sprite.getTextureRect();
  set_sprite_texture_height(sprite, rect.height + amount);
}

sf::Vector2f get_middle_top_transform(const sf::Sprite& sprite,
                                      const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({width / 2, 0.f + additional_value});
}

sf::Vector2f get_middle_bot_transform(const sf::Sprite& sprite,
                                      const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({width / 2, height + additional_value});
}

TracesHandler::TracesHandler(const sf::Texture& texture, sf::Sprite& tankSprite,
                             const sf::Vector2f& startingPosition)
    : mTracksTexture(texture),
      mTankSprite(tankSprite),
      mLastTankPos(startingPosition),
      mMaxTextureHeight(mTracksTexture.getSize().y - 4) {}

float TracesHandler::get_max_texture_height() const { return mMaxTextureHeight; }

const std::deque<sf::Sprite>& TracesHandler::get_traces() const { return mTraces; }

void TracesHandler::update() {
  if (is_move_zero()) {
    mLastTankPos = mTankSprite.getPosition();
    return;
  }
  const auto& move = mTankSprite.getPosition() - mLastTankPos;
  mLastTankPos = mTankSprite.getPosition();
  int current_move_texture_height = get_current_move_texture_height(hypot(move));

  if (mTraces.empty() || is_move_angle_changed(move)) {
    mTraces.emplace_back(get_sprite(move, current_move_texture_height));
    return;
  }

  if (new_height_exceeds_max_height(current_move_texture_height)) {
    const int new_trace_height = get_new_trace_height(current_move_texture_height);
    set_sprite_texture_height(mTraces.back(), mMaxTextureHeight);
    mTraces.emplace_back(get_sprite(move, new_trace_height));
  } else {
    increase_sprite_height(mTraces.back(), current_move_texture_height);
  }
}

bool TracesHandler::is_move_zero() const { return equal(mTankSprite.getPosition(), mLastTankPos); }

int TracesHandler::get_current_move_texture_height(const float move_distance) {
  mTextureHeight += move_distance;
  int return_value = static_cast<int>(mTextureHeight);
  mTextureHeight -= return_value;
  return return_value;
}

bool TracesHandler::is_move_angle_changed(const sf::Vector2f& move) const {
  return !mTraces.empty() && !equal(mTraces.back().getRotation(), get_opposite_angle(move), 1.0);
}

float TracesHandler::get_opposite_angle(const sf::Vector2f& move) const {
  float move_angle = get_angle(move) - 180.f;
  if (move_angle < 0.f) {
    move_angle = 360.f + move_angle;
  }
  return move_angle;
}

sf::Sprite TracesHandler::get_sprite(const sf::Vector2f& move, const int sprite_height) const {
  sf::Sprite sprite(mTracksTexture);
  const auto& rect = sprite.getTextureRect();
  sprite.setOrigin(rect.width / 2, 0);
  sprite.setRotation(get_opposite_angle(move));
  if (is_moving_forward(move)) {
    sprite.setPosition(get_middle_bot_transform(mTankSprite, sprite_height));
  } else {
    sprite.setPosition(get_middle_top_transform(mTankSprite, -sprite_height));
  }
  set_sprite_texture_height(sprite, sprite_height);
  return sprite;
}

bool TracesHandler::is_moving_forward(const sf::Vector2f& move) const {
  return equal(get_angle(move), mTankSprite.getRotation(), 1.0);
}

bool TracesHandler::new_height_exceeds_max_height(const int sprite_height) const {
  const auto& trace_rect = mTraces.back().getTextureRect();
  return sprite_height + trace_rect.height > mMaxTextureHeight;
}

int TracesHandler::get_new_trace_height(const int sprite_height) const {
  const auto& trace_rect = mTraces.back().getTextureRect();
  return sprite_height - (mMaxTextureHeight - trace_rect.height);
}
