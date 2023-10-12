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

Board::Board() : mBackground(mStore) {
  constexpr float TANK_X = WIDTH / 2.0f;
  constexpr float TANK_Y = 50.f;
  constexpr float TANK2_X = WIDTH / 2.0f;
  constexpr float TANK2_Y = 400.0f;
  mKeyboardPlayer =
      std::make_unique<KeyboardPlayer>(*this, TankFactory::Random(mStore, TANK_X, TANK_Y));
  mDummyPlayer =
      std::make_unique<DummyPlayer>(*this, TankFactory::Random(mStore, TANK2_X, TANK2_Y));
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
  mText.setFont(mFont);
}

void Board::register_missile(const Missle& missile) { mMissles.push_back(missile); }

void Board::draw(sf::RenderWindow &window) {
  mBackground.draw(window);
  if (mKeyboardPlayer) {
    mKeyboardPlayer->draw(window);
  }
  if (mDummyPlayer) {
    mDummyPlayer->draw(window);
  }
  for (auto& missle : mMissles) {
    missle.draw(window);
  }
  display_score(window);
}

void Board::process_events(const sf::Event &event) {
  if (mKeyboardPlayer) {
    mKeyboardPlayer->handle_events(event);
  }
}

void Board::update() {
  if (mDummyPlayer) {
    mDummyPlayer->update();
  }
  if (mKeyboardPlayer) {
    mKeyboardPlayer->update();
  }
  remove_missles();
  remove_players();
}

void Board::display_score(sf::RenderWindow &window) {
        mText.setString("Player: " + std::to_string(mPlayerScore) + " Enemy: " + std::to_string(mEnemyScore));
        mText.setCharacterSize(24);
        mText.setFillColor(sf::Color::White);
        mText.setPosition(10.0f, 10.0f);
        mText.setStyle(sf::Text::Bold);
        window.draw(mText);
}

void Board::remove_missles() {
  std::erase_if(mMissles, [](const auto& missle) -> bool {
    const auto [x, y] = missle.get_pos();
    return (x > WIDTH || y > HEIGHT || x < 0 || y < 0);
  });
}

void Board::remove_players() {
  std::vector<Missle> missiles_collided{};
  auto remove_player_if_hit = [this, &missiles_collided](auto& player) -> bool{
    if (!player) {
      return false;
    }
    const auto& it =
        std::find_if(mMissles.cbegin(), mMissles.cend(), [&player](const auto& missile) {
          return player->get_tank().get_body_rect().contains(missile.get_pos());
        });

    if (it != mMissles.cend()) {
      player->get_tank().take_damage(25.0f);
      missiles_collided.push_back(*it);
      if (!player->get_tank().is_alive()) {
        player.reset();
        return true;
      }
    }
    return false;
  };

  if(remove_player_if_hit(mKeyboardPlayer)) {
      mEnemyScore++;
      reset_tanks();
  }
  if(remove_player_if_hit(mDummyPlayer)){
      mPlayerScore++;
      reset_tanks();
  }

  std::erase_if(mMissles, [&missiles_collided](const auto& missile) {
    return std::any_of(missiles_collided.cbegin(), missiles_collided.cend(),
                       [&missile](const auto& m) { return m == missile; });
  });
}

void Board::reset_tanks() {
        constexpr float TANK_X = WIDTH / 2.0f;
        constexpr float TANK_Y = 50.f;
        constexpr float TANK2_X = WIDTH / 2.0f;
        constexpr float TANK2_Y = 400.0f;
        mKeyboardPlayer =
        std::make_unique<KeyboardPlayer>(*this, TankFactory::Random(mStore, TANK_X, TANK_Y));
        mDummyPlayer =
        std::make_unique<DummyPlayer>(*this, TankFactory::Random(mStore, TANK2_X, TANK2_Y));
}

bool Board::is_gameover() const { return mIsGameover; }