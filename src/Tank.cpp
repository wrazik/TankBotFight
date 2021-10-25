#include "Tank.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>

#include "Engine.hpp"
#include "Size.hpp"
#include "TextureStore.hpp"
#include "TracesHandler.hpp"
#include "utility.hpp"

TankPart::TankPart(sf::Texture &texture) {
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(width / 2.f, height / 2.f);
  std::cout << "TANKPART::TANKPART SPRITE ADDRESS: " << &mSprite << "\n";
}

void TankPart::rotate(const Rotation r) { mRotation = r; }

void TankPart::set_rotation(const int angle) { mSprite.setRotation(angle); }

float TankPart::get_rotation() const { return mSprite.getRotation(); }

sf::Sprite &TankPart::get_sprite() { return mSprite; }

const sf::Sprite &TankPart::get_sprite() const { return mSprite; }

void TankPart::update() {
  switch (mRotation) {
    case Rotation::Clockwise:
      mSprite.rotate(10);
      break;
    case Rotation::Counterclockwise:
      mSprite.rotate(-10);
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
           sf::Texture &tracks, std::unique_ptr<Engine> &&engine)
    : mPos({x, y}),
      mBody(body),
      mTower(tower),
      mShot(shot),
      mTracks(tracks),
      mEngine(std::move(engine)),
      mTracesHandler(std::make_unique<TracesHandler>(tracks, mBody.get_sprite(), mPos)) {
  std::cout << "TANK::TANK BODY SPRITE ADDRESS: " << &mBody.get_sprite() << "\n";
  std::cout << "TANK::TANK TANK ADDRESS: " << this << "\n";
  set_rotation(180);
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
      mTracks(rhs.mTracks),
      mEngine(rhs.mEngine->copy()),
      mTracesHandler(std::make_unique<TracesHandler>(*mTracks.get_sprite().getTexture(), mBody.get_sprite(), mPos)) {
  std::cout << "TANK copy constructor\n";
}

Tank::Tank(Tank &&rhs)
    : mPos(std::move(rhs.mPos)),
      mCurrentSpeed(std::move(rhs.mCurrentSpeed)),
      mShotStart(std::move(rhs.mShotStart)),
      mDrawShot(std::move(rhs.mDrawShot)),
      mBody(std::move(rhs.mBody)),
      mTower(std::move(rhs.mTower)),
      mShot(std::move(rhs.mShot)),
      mTracks(std::move(rhs.mTracks)),
      mEngine(std::move(rhs.mEngine)),
      mTracesHandler(std::make_unique<TracesHandler>(*mTracks.get_sprite().getTexture(), mBody.get_sprite(), mPos)) {
        std::cout << "TANK::TANK MOVE CTOR BODY ADDRESS: " << &mBody.get_sprite() << "\n";
        std::cout << "TANK::TANK MOVE CTOR TANK ADDRESS: " << this << "\n";
      }

Tank &Tank::operator=(const Tank &rhs) {
  std::cout << "TANK copy operator=\n";

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
  mTracks = rhs.mTracks;
  mEngine = rhs.mEngine->copy();
  mTracesHandler = std::make_unique<TracesHandler>(*mTracks.get_sprite().getTexture(), mBody.get_sprite(), mPos);
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
  mTracks = std::move(rhs.mTracks);
  mEngine = std::move(rhs.mEngine);
  mTracesHandler = std::make_unique<TracesHandler>(*mTracks.get_sprite().getTexture(), mBody.get_sprite(), mPos);
  return *this;
}

void Tank::set_gear(Gear gear) { mEngine->set_gear(gear); }

void Tank::rotate_body(Rotation r) {
  mBody.rotate(r);
  mTracks.rotate(r);
}

void Tank::rotate_tower(Rotation r) {
  mTower.rotate(r);
  mShot.rotate(r);
}

void Tank::set_rotation(const int angle) {
  mTower.set_rotation(angle);
  mBody.set_rotation(angle);
  mShot.set_rotation(angle);
  mTracks.set_rotation(angle);
}

sf::Vector2f Tank::get_position() { return mPos; }

void Tank::update() {
  mBody.update();
  mTower.update();
  mShot.update();
  mEngine->update();
  // we have a position update; however tank elements are not yet updated
  update_position();
  // std::cout << "TANK::UPDATE TANK POSITION: ";
  // print_point(mBody.get_sprite().getPosition());
  mTracesHandler->update();

  update_shot();
}

void Tank::update_position() {
  const auto& delta = mEngine->get_position_delta(to_radians(mBody.get_rotation()));
  mPos += delta;
  
  mBody.get_sprite().setPosition(mPos);
  mTower.get_sprite().setPosition(mPos);
  mShot.get_sprite().setPosition(mPos);
}

void Tank::update_shot() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mShotStart);
  if (elapsed > shotAnimationDuration) {
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
  auto getShotAnimationPosition = [x = mPos.x, y = mPos.y](float towerRotation) {
    return sf::Vector2f{
        x + shotAnimationDistance * static_cast<float>(cos(to_radians(towerRotation - 90))),
        y + shotAnimationDistance * static_cast<float>(sin(to_radians(towerRotation - 90)))};
  };
  auto shotAnimationPosition = getShotAnimationPosition(mTower.get_rotation());
  mShot.draw(window, shotAnimationPosition.x, shotAnimationPosition.y);
}

void Tank::draw_tracks(sf::RenderWindow &window) {
  for (const auto &sprite : mTracesHandler->getTraces()) {
    window.draw(sprite);
  }
}
