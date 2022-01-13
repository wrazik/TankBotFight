#include "Tank.hpp"

#include <cmath>

#include "Size.hpp"
#include "TextureStore.hpp"
#include "utility.hpp"

constexpr int TANK_INITIAL_ROTATION = 180;
constexpr int ROTATION_OFFSET = 90;
constexpr int TANK_PART_ROTATE = 10;
constexpr int SHOT_ANIMATION_DISTANCE = 30;
constexpr std::chrono::milliseconds SHOT_ANIMATION_DURATION = std::chrono::milliseconds(100);

TankPart::TankPart(sf::Texture &texture) {
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(width / 2.f, height / 2.f);
}

void TankPart::rotate(const Rotation r) { mRotation = r; }

void TankPart::set_rotation(const int angle) { mSprite.setRotation(angle); }

float TankPart::get_rotation() const { return mSprite.getRotation(); }

sf::Sprite &TankPart::get_sprite() { return mSprite; }

const sf::Sprite &TankPart::get_sprite() const { return mSprite; }

void TankPart::update() {
  switch (mRotation) {
    case Rotation::Clockwise:
      mSprite.rotate(TANK_PART_ROTATE);
      break;
    case Rotation::Counterclockwise:
      mSprite.rotate(-TANK_PART_ROTATE);
      break;
    case Rotation::None:
      break;
  }
}

void TankPart::draw(sf::RenderWindow &window, const float x, const float y) {
  mSprite.setPosition(x, y);
  window.draw(mSprite);
}

Tank::Tank(float x, float y, sf::Texture &body, sf::Texture &tower, sf::Texture &shot,
           sf::Texture &tracks, std::unique_ptr<Engine> &&engine,
           const TracesHandlerConfig &traces_handler_config)
    : mPos({x, y}),
      mBody(body),
      mTower(tower),
      mShot(shot),
      mEngine(std::move(engine)),
      mTracesHandler(std::make_unique<TracesHandler>(tracks, mBody.get_sprite(), mPos,
                                                     traces_handler_config)) {
  set_rotation(TANK_INITIAL_ROTATION);
  mBody.get_sprite().setPosition(mPos);
  mTower.get_sprite().setPosition(mPos);
  mShot.get_sprite().setPosition(mPos);
}

Tank::Tank(const Tank &rhs)
    : mPos(rhs.mPos),
      mCurrentSpeed(rhs.mCurrentSpeed),
      mShotStart(rhs.mShotStart),
      mDrawShot(rhs.mDrawShot),
      mBody(rhs.mBody),
      mTower(rhs.mTower),
      mShot(rhs.mShot),
      mEngine(rhs.mEngine->copy()),
      mTracesHandler(std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(),
                                                     mBody.get_sprite(), mPos,
                                                     rhs.mTracesHandler->get_config())) {}

Tank::Tank(Tank &&rhs)
    : mPos(std::move(rhs.mPos)),
      mCurrentSpeed(std::move(rhs.mCurrentSpeed)),
      mShotStart(std::move(rhs.mShotStart)),
      mDrawShot(std::move(rhs.mDrawShot)),
      mBody(std::move(rhs.mBody)),
      mTower(std::move(rhs.mTower)),
      mShot(std::move(rhs.mShot)),
      mEngine(std::move(rhs.mEngine)),
      mTracesHandler(std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(),
                                                     mBody.get_sprite(), mPos,
                                                     rhs.mTracesHandler->get_config())) {}

Tank &Tank::operator=(const Tank &rhs) {
  if (this == &rhs) {
    return *this;
  }
  mPos = rhs.mPos;
  mCurrentSpeed = rhs.mCurrentSpeed;
  mShotStart = rhs.mShotStart;
  mDrawShot = rhs.mDrawShot;
  mBody = rhs.mBody;
  mTower = rhs.mTower;
  mShot = rhs.mShot;
  mEngine = rhs.mEngine->copy();
  mTracesHandler =
      std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(), mBody.get_sprite(),
                                      mPos, rhs.mTracesHandler->get_config());
  return *this;
}

Tank &Tank::operator=(Tank &&rhs) {
  if (this == &rhs) {
    return *this;
  }
  mPos = std::move(rhs.mPos);
  mCurrentSpeed = std::move(rhs.mCurrentSpeed);
  mShotStart = std::move(rhs.mShotStart);
  mDrawShot = std::move(rhs.mDrawShot);
  mBody = std::move(rhs.mBody);
  mTower = std::move(rhs.mTower);
  mShot = std::move(rhs.mShot);
  mEngine = std::move(rhs.mEngine);
  mTracesHandler =
      std::make_unique<TracesHandler>(rhs.mTracesHandler->get_trace_texture(), mBody.get_sprite(),
                                      mPos, rhs.mTracesHandler->get_config());
  return *this;
}

void Tank::set_gear(Gear gear) { mEngine->set_gear(gear); }

void Tank::rotate_body(Rotation r) { mBody.rotate(r); }

void Tank::rotate_tower(Rotation r) {
  mTower.rotate(r);
  mShot.rotate(r);
}

void Tank::set_rotation(const int angle) {
  mTower.set_rotation(angle);
  mBody.set_rotation(angle);
  mShot.set_rotation(angle);
}

sf::Vector2f Tank::get_position() { return mPos; }

void Tank::update() {
  mBody.update();
  mTower.update();
  mShot.update();
  mEngine->update();
  update_position();
  mTracesHandler->update();
  update_shot();
}

void Tank::update_position() {
  const auto &delta = mEngine->get_position_delta(to_radians(mBody.get_rotation()));
  const auto new_pos = mPos + delta;
  if (is_sprite_x_in_board(new_pos.x, mBody.get_sprite())) {
    mPos.x = new_pos.x;
  }
  if (is_sprite_y_in_board(new_pos.y, mBody.get_sprite())) {
    mPos.y = new_pos.y;
  }
  mBody.get_sprite().setPosition(mPos);
  mTower.get_sprite().setPosition(mPos);
  mShot.get_sprite().setPosition(mPos);
}

void Tank::update_shot() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mShotStart);
  if (elapsed > SHOT_ANIMATION_DURATION) {
    mDrawShot = false;
  }
}

float Tank::get_current_speed() { return mEngine->get_current_speed(); }

void Tank::shot() {
  mShotStart = std::chrono::system_clock::now();
  mDrawShot = true;
}

float Tank::get_tower_rotation() const { return mTower.get_rotation(); }

void Tank::draw(sf::RenderWindow &window) {
  mBody.draw(window, mPos.x, mPos.y);
  mTower.draw(window, mPos.x, mPos.y);
  if (mDrawShot) {
    draw_shot(window);
  }
  draw_tracks(window);
}

void Tank::draw_shot(sf::RenderWindow &window) {
  auto get_shot_animation_pos = [x = mPos.x, y = mPos.y](float tower_rotation) {
    return sf::Vector2f{
        x + SHOT_ANIMATION_DISTANCE *
                static_cast<float>(cos(to_radians(tower_rotation - ROTATION_OFFSET))),
        y + SHOT_ANIMATION_DISTANCE *
                static_cast<float>(sin(to_radians(tower_rotation - ROTATION_OFFSET)))};
  };
  const auto shot_animation_pos = get_shot_animation_pos(mTower.get_rotation());
  mShot.draw(window, shot_animation_pos.x, shot_animation_pos.y);
}

void Tank::draw_tracks(sf::RenderWindow &window) {
  for (const auto &trace : mTracesHandler->get_traces()) {
    window.draw(trace);
  }
}
