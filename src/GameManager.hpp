#pragma once

#include <SFML/Graphics.hpp>

#include "Board.hpp"

enum class GameManagerState {
  MainMenu,
  Started,
  Exit,
};

class GameManager {
 public:
  GameManager();

 private:
  // objects
  GameManagerState mGameManagerState = GameManagerState::MainMenu;
  sf::RenderWindow mWindow;
  Board mBoard;

  // methods
 public:
  void start();
  void transitState(GameManagerState desired_state);
  void performStateMachine(const sf::Event& event);
};