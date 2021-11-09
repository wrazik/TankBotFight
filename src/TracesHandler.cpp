#include "TracesHandler.hpp"

#include "utility.hpp"

sf::Vector2f get_middle_top_transform(const sf::Sprite& sprite,
                                      const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint({left + width / 2.f, top + 0.f + additional_value});
}

sf::Vector2f get_middle_bot_transform(const sf::Sprite& sprite,
                                      const float additional_value = 0.f) {
  const auto& [left, top, width, height] = sprite.getLocalBounds();
  return sprite.getTransform().transformPoint(
      {left + width / 2.f, top + height + additional_value});
}

TracesHandler::TracesHandler(const sf::Texture& texture, sf::Sprite& tank_sprite,
                             const sf::Vector2f& start_pos, const int max_trace_age,
                             const float decay_rate)
    : mTracksTexture(texture),
      mTankSprite(tank_sprite),
      mLastTankPos(start_pos),
      mMaxTextureHeight(mTracksTexture.getSize().y),
      mMaxTraceAge(max_trace_age),
      mTraceDecayRate(decay_rate) {}

float TracesHandler::get_max_texture_height() const { return mMaxTextureHeight; }

std::deque<Trace> TracesHandler::get_traces() const { return mTraces; }

const sf::Texture& TracesHandler::get_trace_texture() const { return mTracksTexture; }

int TracesHandler::get_max_trace_age() const { return mMaxTraceAge; }

float TracesHandler::get_trace_decay_rate() const { return mTraceDecayRate; }

void TracesHandler::update() {
  const auto& move = mTankSprite.getPosition() - mLastTankPos;
  mLastTankPos = mTankSprite.getPosition();
  update_traces_age();
  decay_traces();
  if (equal(move, {0.f, 0.f})) {
    return;
  }
  if (mTraces.empty() || is_move_angle_changed(move)) {
    add_trace(make_trace(move));
    return;
  }
  mTraces.back().increase_height(hypot(move));
}

void TracesHandler::update_traces_age() {
  for (short& age : mTracesAge) {
    if (age < mMaxTraceAge) {
      age++;
    }
  }
}

void TracesHandler::decay_traces() {
  if (mTracesAge.size() <= 0) {
    return;
  }
  if (mTracesAge.front() >= mMaxTraceAge) {
    const float trace_height = mTraces.front().get_height();
    const float decrease_by = std::min(mTraceDecayRate * mMaxTextureHeight, trace_height);
    if (decrease_by < mTraceDecayRate * mMaxTextureHeight) {
      remove_trace();
      return;
    }
    mTraces.front().decrease_height(decrease_by);
  }
}

void TracesHandler::add_trace(const Trace& trace) {
  mTraces.emplace_back(trace);
  mTracesAge.emplace_back(0);
}

void TracesHandler::remove_trace() {
  mTraces.pop_front();
  mTracesAge.pop_front();
}

bool TracesHandler::is_move_angle_changed(const sf::Vector2f& move) const {
  return !mTraces.empty() &&
         !equal(mTraces.back().get_rotation(), get_opposite_angle(get_angle(move)), 1.0);
}

float TracesHandler::get_opposite_angle(const float angle) const {
  float opposite_angle = angle - 180.f;
  if (opposite_angle < 0.f) {
    opposite_angle = 360.f + opposite_angle;
  }
  return opposite_angle;
}

Trace TracesHandler::make_trace(const sf::Vector2f& move) const {
  const float angle = get_opposite_angle(get_angle(move));
  const float move_distance = hypot(move);
  auto pos = sf::Vector2f{};
  if (is_moving_forward(move)) {
    pos = get_middle_bot_transform(mTankSprite, move_distance);
  } else {
    pos = get_middle_top_transform(mTankSprite, -move_distance);
  }
  return Trace(mTracksTexture, pos, angle, move_distance);
}

bool TracesHandler::is_moving_forward(const sf::Vector2f& move) const {
  return equal(get_angle(move), mTankSprite.getRotation(), 1.0);
}
