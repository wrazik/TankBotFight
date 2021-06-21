#include "Board.hpp"

Board::Board()
  : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight")
  , mBackground(mWindow)
{
  mWindow.setFramerateLimit(1);
}

void
Board::run()
{
  while (mWindow.isOpen()) {

    sf::Event event;
    while (mWindow.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mWindow.close();
      }
    }

    mWindow.clear();
    mBackground.draw();
    mWindow.display();
  }
}
