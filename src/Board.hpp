#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Animation.hpp"
#include "Missle.hpp"
#include "Players/DummyPlayer.hpp"
#include "Players/KeyboardPlayer.hpp"
#include "background/Background.hpp"
class Board {
 public:
  Board();

  void register_missile(const Missle& missile);
  void register_animation(const Animation& animation);
  void run();

 private:
  void remove_missles();
  void update_players();
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
  Sound mTankExplodeSound;
  std::vector<Animation> mAnimations;
};
