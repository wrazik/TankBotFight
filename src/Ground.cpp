#include "Ground.hpp"
#include "Files.hpp"

Ground::Ground(sf::RenderWindow& w, const sf::Texture& t, GroundType gt)
  : mGroundType(gt)
  , mTexture(std::move(t))
  , mWindow(w)
{
  mSprite.setTexture(mTexture);
}

void
Ground::draw(const int x, const int y)
{
  mSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
  mWindow.draw(mSprite);
}
