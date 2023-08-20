#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Missle.hpp"
#include "Players/DummyPlayer.hpp"
#include "Players/KeyboardPlayer.hpp"
#include "background/Background.hpp"

class Board {
 public:
  Board();

  void register_missile(const Missle& missile);
  void run();

 private:
  void remove_missles();
  void remove_players();
  void display_speed();
  void draw();

  TextureStore mStore;
  sf::RenderWindow mWindow;
  Background mBackground;
  std::unique_ptr<KeyboardPlayer> mKeyboardPlayer;
  std::unique_ptr<DummyPlayer> mDummyPlayer;
  std::vector<Missle> mMissles;
  sf::Font mFont;
  sf::Text mText;
};
