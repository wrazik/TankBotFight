#include "Tank.hpp"

#include <cmath>

#include "Engine.hpp"
#include "Size.hpp"
#include "TextureStore.hpp"
#include "utility.hpp"

TankPart::TankPart(sf::Texture &texture) {
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(width / 2.f, height / 2.f);
}

void TankPart::rotate(const Rotation r) { mRotation = r; }

void TankPart::set_rotation(const int angle) { mSprite.setRotation(angle); }

float TankPart::get_rotation() const { return mSprite.getRotation(); }

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
           std::unique_ptr<Engine>&& engine)
    : mPos({x, y}), mBody(body), mTower(tower), mShot(shot), mEngine(std::move(engine)) {
  mTower.set_rotation(180);
  mShot.set_rotation(180);
}

Tank::Tank(const Tank& rhs)
: mPos(rhs.mPos), mBody(rhs.mBody), mTower(rhs.mTower), mShot(rhs.mShot), mEngine(rhs.mEngine->copy()) {
}

Tank& Tank::operator=(const Tank& rhs) {
  mPos = rhs.mPos;
  mCurrentSpeed = rhs.mCurrentSpeed;
  mShotStart = rhs.mShotStart;
  mDrawShot = rhs.mDrawShot;
  mBody = rhs.mBody;
  mTower = rhs.mTower;
  mShot = rhs.mShot;
  mEngine = rhs.mEngine->copy();
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
  update_shot();
}

void Tank::update_position() {
  mPos += mEngine->get_position_delta(to_radians(mBody.get_rotation()));
}

float Tank::get_current_speed() { return mEngine->get_current_speed(); }

void Tank::update_shot() {
  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mShotStart);
  if (elapsed > shotAnimationDuration) {
    mDrawShot = false;
  }
}

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
