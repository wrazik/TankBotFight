#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Missle.hpp"
#include "Tank/Tank.hpp"
#include "background/Background.hpp"

class Board {
 public:
  Board();

  void register_tank();
  void register_missile(const Missle& missile);

  void run();

 private:
  void remove_missles();
  void remove_tanks();
  void display_speed();
  void draw();

  TextureStore mStore;
  sf::RenderWindow mWindow;
  Background mBackground;
  std::vector<std::shared_ptr<Tank>> mTanks;
  std::vector<Missle> mMissles;
  sf::Font mFont;
  sf::Text mText;
};
