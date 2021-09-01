#pragma once

#include <SFML/Graphics.hpp>

#include "Missle.hpp"
#include "SquareRootEngine.hpp"
#include "Tank.hpp"
#include "background/Background.hpp"

class Board {
 public:
  Board();

  void register_tank();
  void fire_missle(const float angle, const float x, const float y);

  void run();

 private:
  void remove_missles();
  void display_speed();

  TextureStore mStore;
  sf::RenderWindow mWindow;
  Background mBackground;
  std::vector<Tank> mTanks;
  std::vector<Missle> mMissles;
  SquareRootEngine mEngine;
  sf::Font font;
  sf::Text text;
};
