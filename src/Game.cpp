//
// Created by wrazik on 24.08.23.
//

#include "Game.hpp"

Game::Game(): mWindow(sf::VideoMode(WIDTH, HEIGHT), "Tanks") {
  mWindow.setFramerateLimit(30);
}

void Game::run() {
  while (mWindow.isOpen()) {
    sf::Event event{};

    mWindow.clear();

    if (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mWindow.close();
      }

      mBoard.process_events(event);
    }

    switch(mState) {
      case GameState::Playing:
        mBoard.draw(mWindow);
        mBoard.update();
        break;
      case GameState::GameOver:
        // baord reset
        return;
    }
    mWindow.display();
  }
}
