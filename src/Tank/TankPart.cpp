#include "TankPart.hpp"

#include <gsl/gsl>

constexpr int TANK_PART_ROTATE = 10;

TankPart::TankPart(sf::Texture &texture) {
  mSprite.setTexture(texture);
  const auto [width, height] = texture.getSize();
  mSprite.setOrigin(gsl::narrow<float>(width) / 2.f, gsl::narrow<float>(height) / 2.f);
}

void TankPart::rotate(const Rotation r) { mRotation = r; }

void TankPart::set_rotation(const float angle) { mSprite.setRotation(angle); }

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

void TankPart::draw(sf::RenderWindow &window) { window.draw(mSprite); }
