#pragma once

#include "Background.hpp"
#include <SFML/Graphics.hpp>

class Board
{
public:
  Board();

  void run();

private:
  sf::RenderWindow mWindow;
  Background mBackground;
};
