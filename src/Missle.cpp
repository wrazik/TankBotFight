#include "Missle.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <gsl/gsl>

#include "Size.hpp"

Missle::Missle(sf::Texture& texture, const float angle, const float x, const float y)
    : mPos({x, y}), mAngle(angle) {
  mSprite.setTexture(texture);
  mSprite.setPosition(mPos.x, mPos.y);
  mSprite.setRotation(angle);
}
void Missle::draw(sf::RenderWindow& window) {
  update();
  mSprite.setPosition(mPos.x, mPos.y);
  window.draw(mSprite);
}

sf::Vector2f Missle::get_pos() const { return mPos; }

void Missle::update() {
  const auto rotation_degree = mAngle - 90;
  const auto rotation_radians = PI / 180.f * rotation_degree;

  mPos.x += mSpeed * gsl::narrow_cast<float>(std::cos(rotation_radians));
  mPos.y += mSpeed * gsl::narrow_cast<float>(std::sin(rotation_radians));
}
