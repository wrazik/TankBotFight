#pragma once

#include "Background.hpp"
#include "Tank.hpp"
#include <SFML/Graphics.hpp>

class Board
{
public:
  Board();

  void register_tank();

  void run();

private:
  TextureStore mStore;
  sf::RenderWindow mWindow;
  Background mBackground;
  std::vector<Tank> mTanks;
};
