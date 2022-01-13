#pragma once
#include <SFML/Graphics.hpp>

enum class SurfaceType {
  Sand,
  Grass,
};

struct GroundType {
  SurfaceType mSurface;
  bool mIsRoad;
};

class Ground {
 public:
  Ground(sf::Texture& texture);
  void draw(sf::RenderWindow& window, int x, int y);

 private:
  sf::Sprite mSprite;
};
