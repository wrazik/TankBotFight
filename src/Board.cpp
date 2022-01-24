#include "Board.hpp"

#include <string>

#include "Controllers/DummyController.hpp"
#include "Controllers/KeyboardController.hpp"
#include "Files.hpp"
#include "Random.hpp"
#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TankFactory.hpp"
#include "TracesHandler.hpp"

Board::Board() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"), mBackground(mStore) {
  mWindow.setFramerateLimit(30);
}

void Board::register_tank() {
  using namespace std::string_literals;
  constexpr float TANK_X = WIDTH / 2.0f;
  constexpr float TANK_Y = 50.f;

  constexpr float TANK2_X = WIDTH / 2.0f;
  constexpr float TANK2_Y = 400.0f;

  mTanks.emplace_back(TankFactory::Random(mStore, TANK_X, TANK_Y));
  mTanks.emplace_back(TankFactory::Random(mStore, TANK2_X, TANK2_Y));
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  mText.setFont(mFont);
}

void Board::fire_missle(Tank& tank) {
  const auto angle = tank.get_tower_rotation();
  const auto [x, y] = tank.get_position();
  auto& missle_texture = mStore.get_texture("bulletDark3.png");
  mMissles.emplace_back(missle_texture, angle, x, y);
  tank.shot();
}

void Board::draw() {
  mWindow.clear();
  mBackground.draw(mWindow);
  for (auto& tank : mTanks) {
    tank.draw(mWindow);
  }
  for (auto& missle : mMissles) {
    missle.draw(mWindow);
  }
  display_speed();
  mWindow.display();
}

void Board::run() {
  KeyboardController keyboard_controller(mTanks[0], *this);
  DummyController dummyController(mTanks[1], *this);

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

    for (auto& tank : mTanks) {
      tank.update();
    }
    dummyController.update();
    draw();
    remove_missles();
  }
}

void Board::display_speed() {
  mText.setString(std::to_string(mTanks[0].get_current_speed()));
  mWindow.draw(mText);
}

void Board::remove_missles() {
  std::erase_if(mMissles, [](const auto& missle) -> bool {
    const auto [x, y] = missle.get_pos();
    return (x > WIDTH || y > HEIGHT || x < 0 || y < 0);
  });
}
