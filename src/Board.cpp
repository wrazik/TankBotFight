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

Board::Board(sf::RenderWindow& window) : mWindow{window}, mBackground(mStore) {
  constexpr float TANK_X = WIDTH / 2.0f;
  constexpr float TANK_Y = 50.f;
  constexpr float TANK2_X = WIDTH / 2.0f;
  constexpr float TANK2_Y = 400.0f;
  Sound tank_shot_sound("tank_shot.flac");
  mWindow.setFramerateLimit(30);
  mKeyboardPlayer = std::make_unique<KeyboardPlayer>(
      *this, TankFactory::Random(mStore, TANK_X, TANK_Y, tank_shot_sound));
  mDummyPlayer = std::make_unique<DummyPlayer>(
      *this, TankFactory::Random(mStore, TANK2_X, TANK2_Y, tank_shot_sound));
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  mText.setFont(mFont);
}

void Board::register_missile(const Missle& missile) { mMissles.push_back(missile); }

void Board::draw() {
  mBackground.draw(mWindow);
  if (mKeyboardPlayer) {
    mKeyboardPlayer->draw(mWindow);
  }
  if (mDummyPlayer) {
    mDummyPlayer->draw(mWindow);
  }
  for (auto& missle : mMissles) {
    missle.draw(mWindow);
  }
  display_speed();
}

void Board::play(const sf::Event& event) {
  if (mKeyboardPlayer) {
    mKeyboardPlayer->handle_events(event);
  }

  if (mDummyPlayer) {
    mDummyPlayer->update();
  }

  if (mKeyboardPlayer) {
    mKeyboardPlayer->update();
  }
  draw();
  remove_missles();
  update_players();
}

void Board::display_speed() {
  if (mKeyboardPlayer) {
    mText.setString(std::to_string(mKeyboardPlayer->get_tank().get_current_speed()));
    mWindow.draw(mText);
  }
}

void Board::remove_missles() {
  std::erase_if(mMissles, [](const auto& missle) -> bool {
    const auto [x, y] = missle.get_pos();
    return (x > WIDTH || y > HEIGHT || x < 0 || y < 0);
  });
}

void Board::update_players() {
  std::vector<Missle> missiles_collided{};
  auto update_player_if_hit = [this, &missiles_collided](auto& player) {
    if (!player) {
      return;
    }
    const auto& it =
        std::find_if(mMissles.cbegin(), mMissles.cend(), [&player](const auto& missile) {
          return player->get_tank().get_body_rect().contains(missile.get_pos());
        });
    if (it == mMissles.cend()) {
      return;
    }
    player->get_tank().take_damage((*it).get_damage());
    if (!player->get_tank().is_alive()) {
      player.reset();
    }
    missiles_collided.push_back(*it);
  };

  update_player_if_hit(mKeyboardPlayer);
  update_player_if_hit(mDummyPlayer);

  std::erase_if(mMissles, [&missiles_collided](const auto& missile) {
    return std::any_of(missiles_collided.cbegin(), missiles_collided.cend(),
                       [&missile](const auto& m) { return m == missile; });
  });
}
