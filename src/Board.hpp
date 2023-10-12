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

  void draw(sf::RenderWindow& window);
  void process_events(const sf::Event& event);
  void register_missile(const Missle& missile);
  void update();
  bool is_gameover() const;

 private:
  void remove_missles();
  void remove_players();

  TextureStore mStore;
  Background mBackground;
  std::unique_ptr<KeyboardPlayer> mKeyboardPlayer;
  std::unique_ptr<DummyPlayer> mDummyPlayer;
  std::vector<Missle> mMissles;
  sf::Font mFont;
  sf::Text mText;
  bool mIsGameover = false;
  int mPlayerScore = 0;
  int mEnemyScore = 0;
  void display_score(sf::RenderWindow& window);
  void reset_tanks();
};
