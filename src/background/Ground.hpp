#pragma once
#include <SFML/Graphics.hpp>

enum class Surface {
  Sand,
  Grass,
};

struct GroundType {
    Surface mSurface;
    bool mIsRoad;
};

class Ground {
 public:
  Ground(sf::Texture& texture);
  void draw(sf::RenderWindow& window, const int x, const int y);

 private:
  sf::Sprite mSprite;
};
