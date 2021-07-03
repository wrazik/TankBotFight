#include "Board.hpp"

#include <string>

#include "KeyboardController.hpp"
#include "Random.hpp"
#include "Size.hpp"

Board::Board() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"), mBackground(mStore) {
  mWindow.setFramerateLimit(30);
}

void Board::register_tank() {
  using namespace std::string_literals;
  auto& body_texture = mStore.get_texture(one_of("tankBody_red.png"s, "tankBody_dark.png"s,
                                                 "tankBody_blue.png"s, "tankBody_green.png"s));
  body_texture.setSmooth(true);
  auto& tower_texture =
      mStore.get_texture(one_of("tankDark_barrel2_outline.png", "tankRed_barrel2_outline.png",
                                "tankGreen_barrel2_outline.png", "tankBlue_barrel2_outline.png"));
  tower_texture.setSmooth(true);
  auto tank = Tank(WIDTH / 2.0f, 50.0f, body_texture, tower_texture);
  tank.set_rotation(180);
  mTanks.push_back(std::move(tank));
}

void Board::fire_missle(const float angle, const float x, const float y) {
  auto& missle_texture = mStore.get_texture("bulletDark3.png");
  mMissles.emplace_back(missle_texture, angle, x, y);
}

void Board::run() {
  KeyboardController keyboard_controller(mTanks[0], *this);

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
    for (auto& missle : mMissles) {
      missle.draw(mWindow);
    }
    remove_missles();
    mWindow.display();
  }
}

void Board::remove_missles() {
  std::erase_if(mMissles, [](const auto& missle) -> bool {
    const auto [x, y] = missle.get_pos();
    return (x > WIDTH || y > HEIGHT || x < 0 || y < 0);
  });
}
