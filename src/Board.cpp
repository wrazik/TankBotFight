#include "Board.hpp"

#include "KeyboardController.hpp"

Board::Board() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"), mBackground(mStore) {
  mWindow.setFramerateLimit(30);
}

void Board::register_tank() {
  auto& body_texture = mStore.get_texture("tankBody_red.png");
  auto& tower_texture = mStore.get_texture("tankDark_barrel2_outline.png");
  mTanks.emplace_back(WIDTH / 2.0f, 50.0f, body_texture, tower_texture);
}

void Board::run() {
  KeyboardController keyboard_controller(mTanks[0]);

  while (mWindow.isOpen()) {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mWindow.close();
      }
      keyboard_controller.update(event);
    }

    mWindow.clear();
    mBackground.draw(mWindow);
    for (auto& tank : mTanks) {
      tank.draw(mWindow);
    }
    mWindow.display();
  }
}
