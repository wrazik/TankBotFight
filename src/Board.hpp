#pragma once

#include <SFML/Graphics.hpp>

#include "Missle.hpp"
#include "Tank.hpp"
#include "background/Background.hpp"

class Board {
 public:
  Board();

  void register_tank();
  void fire_missle(Tank& tank);

  void run();

 private:
  void remove_missles();
  void display_speed();
  void draw();

  TextureStore mStore;
  sf::RenderWindow mWindow;
  Background mBackground;
  std::vector<Tank> mTanks;
  std::vector<Missle> mMissles;
  sf::Font mFont;
  sf::Text mText;
};
