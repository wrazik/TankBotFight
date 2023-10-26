#include "GameManager.hpp"

#include "Size.hpp"

GameManager::GameManager()
    : mWindow{sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"}, mBoard{mWindow} {}

void GameManager::start() {
  while (mWindow.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (mWindow.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        mGameManagerState = GameManagerState::Exit;
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mGameManagerState = GameManagerState::Exit;
      }
    }

    // clear the window with black color
    mWindow.clear(sf::Color::Black);

    performStateMachine(event);

    // end the current frame
    mWindow.display();
  }
}
#include <iostream>
void GameManager::performStateMachine(const sf::Event& event) {
  switch (mGameManagerState) {
    case GameManagerState::MainMenu:
      [this]() {
        std::string input;
        std::cout << "Welcome to the game!\n";
        std::cout << "1. Play\n2. Exit\nSelect: ";
        std::cin >> input;
        switch (input[0]) {
          case '1':
            mGameManagerState = GameManagerState::Started;
            break;
          case '2':
            mGameManagerState = GameManagerState::Exit;
            break;
        }
      }();

      break;
    case GameManagerState::Started:
      mBoard.play(event);
      break;
    case GameManagerState::Exit:
      mWindow.close();
      break;
  }
}
