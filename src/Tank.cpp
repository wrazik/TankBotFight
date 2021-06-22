#include "Tank.hpp"
#include <cmath>
#include <numbers>

#include "TextureStore.hpp"

TankPart::TankPart(sf::Texture& texture)
{
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(width / 2.f, height / 2.f);
}

void
TankPart::rotate(const Rotation r)
{
  mRotation = r;
}

void
TankPart::set_rotation(const int angle)
{
  mSprite.setRotation(angle);
}

float
TankPart::get_rotation() const
{
  return mSprite.getRotation();
}

void
TankPart::update()
{
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

void
TankPart::draw(sf::RenderWindow& window, const float x, const float y)
{
  update();
  mSprite.setPosition(x, y);
  window.draw(mSprite);
}

Tank::Tank(float x, float y, sf::Texture& body, sf::Texture& tower)
  : mPos({ x, y })
  , mBody(body)
  , mTower(tower)
{
  mTower.set_rotation(180);
}

void
Tank::rotate_body(Rotation r)
{
  mBody.rotate(r);
}

void
Tank::rotate_tower(Rotation r)
{
  mTower.rotate(r);
}

void
Tank::set_current_speed(float speed)
{
  mCurrentSpeed = speed;
}

void
Tank::update()
{
  const auto rotation_degree = mBody.get_rotation() + 90;
  const auto rotation_radians = std::numbers::pi / 180.f * rotation_degree;

  mPos.x += mCurrentSpeed * std::cos(rotation_radians);
  mPos.y += mCurrentSpeed * std::sin(rotation_radians);
}

void
Tank::draw(sf::RenderWindow& window)
{
  update();
  mBody.draw(window, mPos.x, mPos.y);
  mTower.draw(window, mPos.x, mPos.y);
}
