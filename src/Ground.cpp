#include "Ground.hpp"
#include "Files.hpp"

Ground::Ground(sf::Texture& t, GroundType gt)
  : mGroundType(gt)
{
  mSprite.setTexture(t);
}

void
Ground::draw(sf::RenderWindow& window, const int x, const int y)
{
  mSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
  window.draw(mSprite);
}
