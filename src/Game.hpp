#pragma once
#include "Board.hpp"
#include "Size.hpp"
#include <SFML/Graphics.hpp>

enum class GameState {
  Playing,
  GameOver,
};

class Game {
 public:
  Game();

  void run();

 private:
  void process_events();
  void update();
  void render();

  sf::RenderWindow mWindow;
  Board mBoard;
  GameState mState = GameState::Playing;
  sf::Font mFont;
  sf::Text mText;
};
