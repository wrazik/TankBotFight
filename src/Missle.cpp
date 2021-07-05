#include "Missle.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Size.hpp"

Missle::Missle(sf::Texture& texture, const int angle, const float x, const float y)
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
  const auto rotation_radians = pi / 180.f * rotation_degree;

  mPos.x += mSpeed * std::cos(rotation_radians);
  mPos.y += mSpeed * std::sin(rotation_radians);
}
