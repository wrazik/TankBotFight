#include "Trace.hpp"
#include <cmath>

Trace::Trace(const sf::Texture& tex, const sf::Vector2f& pos, const float angle,
             const float start_height)
    : mTexture(tex), mRotation(angle) {
  const float width = mTexture.getSize().x;
  const auto origin = sf::Vector2f{width / 2, 0.f};
  mTransform.translate(-origin).translate(pos);
  mTransform.rotate(angle, origin);

  mVertices[0].position = {0.f, 0.f};
  mVertices[0].texCoords = {0.f, 0.f};

  mVertices[1].position = {width, 0.f};
  mVertices[1].texCoords = {width, 0.f};

  mVertices[2].position = {width, start_height};
  mVertices[2].texCoords = {width, start_height};

  mVertices[3].position = {0.f, start_height};
  mVertices[3].texCoords = {0.f, start_height};
}

void Trace::increase_height(const float amount) {
  mVertices[2].position += sf::Vector2f{0.f, amount};
  mVertices[2].texCoords += sf::Vector2f{0.f, amount};

  mVertices[3].position += sf::Vector2f{0.f, amount};
  mVertices[3].texCoords += sf::Vector2f{0.f, amount};
}
void Trace::decrease_height(const float amount) {
  mVertices[0].position += sf::Vector2f{0.f, amount};
  mVertices[0].texCoords += sf::Vector2f{0.f, amount};

  mVertices[1].position += sf::Vector2f{0.f, amount};
  mVertices[1].texCoords += sf::Vector2f{0.f, amount};
}

float Trace::get_height() const {
    return std::fabs((mVertices[0].position - mVertices[2].position).y);
}

float Trace::get_rotation() const {
    return mRotation;
}

void Trace::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = &mTexture;
  states.transform *= mTransform;
  target.draw(mVertices, states);
}
