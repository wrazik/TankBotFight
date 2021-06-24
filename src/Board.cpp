#include "Board.hpp"

#include <string>

#include "KeyboardController.hpp"
#include "Random.hpp"

Board::Board() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"), mBackground(mStore) {
  mWindow.setFramerateLimit(30);
}

void Board::register_tank() {
  using namespace std::string_literals;
  auto& body_texture = mStore.get_texture(one_of("tankBody_red.png"s, "tankBody_dark.png"s,
                                                 "tankBody_blue.png"s, "tankBody_green.png"s));
  auto& tower_texture =
      mStore.get_texture(one_of("tankDark_barrel2_outline.png", "tankRed_barrel2_outline.png",
                                "tankGreen_barrel2_outline.png", "tankBlue_barrel2_outline.png"));
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
