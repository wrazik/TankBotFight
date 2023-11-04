#pragma once

#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "MainMenu.hpp"

enum class GameManagerState {
  MainMenu,
  Started,
  Exit,
  InvalidState,
};

class GameManager {
 public:
  GameManager();
  void start();
  void performStateMachine(const sf::Event& event);
  void transitState();

 private:
  // objects
  GameManagerState mGameManagerState = GameManagerState::MainMenu;
  sf::RenderWindow mWindow;
  MainMenu mMainMenu;
  Board mBoard;
  static bool request_state_change;
  static GameManagerState desired_state;

  // friends: buttons' callbacks
  friend void main_menu_start_callback(void);
  friend void main_menu_exit_callback(void);
};