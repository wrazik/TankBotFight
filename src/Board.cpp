#include "Board.hpp"

#include <string>

#include "Files.hpp"
#include "KeyboardController.hpp"
#include "Random.hpp"
#include "Size.hpp"
#include "SquareRootEngine.hpp"
#include "TracesHandler.hpp"

Board::Board() : mWindow(sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"), mBackground(mStore) {
  mWindow.setFramerateLimit(30);
}

void Board::register_tank() {
  using namespace std::string_literals;
  const sf::IntRect TRACKS_TEXTURE_RECT = {0, 0, 37, 48};
  constexpr float TANK_X = WIDTH / 2.0f;
  constexpr float TANK_Y = 50.f;
  constexpr int STEP_COUNT = 70;
  constexpr float MAX_SPEED = 5.f;
  auto& body_texture = mStore.get_texture(one_of("tankBody_red.png"s, "tankBody_dark.png"s,
                                                 "tankBody_blue.png"s, "tankBody_green.png"s));
  body_texture.setSmooth(true);
  auto& tower_texture =
      mStore.get_texture(one_of("tankDark_barrel2_outline.png", "tankRed_barrel2_outline.png",
                                "tankGreen_barrel2_outline.png", "tankBlue_barrel2_outline.png"));
  tower_texture.setSmooth(true);
  auto& shot_texture = mStore.get_texture("shotOrange.png");
  shot_texture.setSmooth(true);
  auto& tracks_texture = mStore.get_texture("tracksSmall.png", TRACKS_TEXTURE_RECT);
  tracks_texture.setSmooth(true);
  tracks_texture.setRepeated(true);
  auto tank = Tank(TANK_X, TANK_Y, body_texture, tower_texture, shot_texture, tracks_texture,
                   std::make_unique<SquareRootEngine>(STEP_COUNT, MAX_SPEED),
                   TracesHandlerConfig{.mMaxTraceAge = 50, .mDecayRate = 0.1f});
  mTanks.emplace_back(std::move(tank));
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  mText.setFont(mFont);
}

void Board::fire_missle(const int angle, const float x, const float y) {
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

    for (auto& tank : mTanks) {
      tank.update();
    }
    mWindow.clear();
    mBackground.draw(mWindow);
    for (auto& tank : mTanks) {
      tank.draw(mWindow);
    }
    for (auto& missle : mMissles) {
      missle.draw(mWindow);
    }
    display_speed();
    remove_missles();
    mWindow.display();
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
