#pragma once
#include <SFML/Graphics.hpp>

enum class GroundType
{
  Sand,
  Grass,
};

inline constexpr int GROUND_WIDTH = 64;
inline constexpr int GROUND_HEIGHT = 64;

class Ground
{
public:
  Ground(sf::Texture& texture, GroundType type);
  void draw(sf::RenderWindow& window, const int x, const int y);

private:
  const GroundType mGroundType;
  sf::Sprite mSprite;
};
