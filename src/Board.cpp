#include "Board.hpp"

#include <string>

#include "Controllers/DummyController.hpp"
#include "Controllers/KeyboardController.hpp"
#include "Files.hpp"
#include "Random.hpp"
#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "Tank/TankFactory.hpp"
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

  mTanks.emplace_back(std::make_shared<Tank>(TankFactory::Random(mStore, TANK_X, TANK_Y)));
  mTanks.emplace_back(std::make_shared<Tank>(TankFactory::Random(mStore, TANK2_X, TANK2_Y)));
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  mText.setFont(mFont);
}

void Board::register_missile(const Missle& missile) { mMissles.push_back(missile); }

void Board::draw() {
  mWindow.clear();
  mBackground.draw(mWindow);
  for (const auto& tank : mTanks) {
    tank->draw(mWindow);
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
    sf::Event event{};
    while (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mWindow.close();
      }
      keyboard_controller.update(event);
    }

    for (const auto& tank : mTanks) {
      tank->update();
    }
    dummyController.update();
    draw();
    remove_missles();
    remove_tanks();
  }
}

void Board::display_speed() {
  if (mTanks.empty()) {
    return;
  }
  mText.setString(std::to_string(mTanks[0]->get_current_speed()));
  mWindow.draw(mText);
}

void Board::remove_missles() {
  std::erase_if(mMissles, [](const auto& missle) -> bool {
    const auto [x, y] = missle.get_pos();
    return (x > WIDTH || y > HEIGHT || x < 0 || y < 0);
  });
}

void Board::remove_tanks() {
  std::vector<Missle> missiles_collided{};

  std::erase_if(mTanks, [this, &missiles_collided](const auto& tank) {
    const auto& body = tank->get_body_rect();
    const auto missile =
        std::find_if(mMissles.cbegin(), mMissles.cend(),
                     [&body](const auto& missile) { return body.contains(missile.get_pos()); });
    if (missile != mMissles.cend()) {
      missiles_collided.push_back(*missile);
    }
    return missile != mMissles.cend();
  });

  std::erase_if(mMissles, [&missiles_collided](const auto& missile) {
    return std::any_of(missiles_collided.cbegin(), missiles_collided.cend(),
                       [&missile](const auto& m) { return m == missile; });
  });
}
