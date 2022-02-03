#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Engine.hpp"

KeyboardController::KeyboardController(const std::shared_ptr<Tank>& tank, Board& board)
    : mTank(tank), mBoard(board) {
  mLastShot = std::chrono::system_clock::now();
}

void KeyboardController::handle_shot() {
  if (mTank.expired()) {
    return;
  }
  const auto now = std::chrono::system_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
  constexpr auto SHOT_COOLDOWN = std::chrono::milliseconds{500};
  if (elapsed >= SHOT_COOLDOWN) {
    mLastShot = now;
    mBoard.fire_missle(*mTank.lock());
  }
}

void KeyboardController::update(const sf::Event& event) {
  if (mTank.expired()) {
    return;
  }
  const auto& tank = mTank.lock();
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      case sf::Keyboard::A:
        tank->rotate_body(Rotation::Counterclockwise);
        break;
      case sf::Keyboard::D:
        tank->rotate_body(Rotation::Clockwise);
        break;
      case sf::Keyboard::Left:
        tank->rotate_tower(Rotation::Counterclockwise);
        break;
      case sf::Keyboard::Right:
        tank->rotate_tower(Rotation::Clockwise);
        break;
      case sf::Keyboard::W:
        tank->set_gear(Gear::Drive);
        break;
      case sf::Keyboard::S:
        tank->set_gear(Gear::Reverse);
        break;
      case sf::Keyboard::Space:
        handle_shot();
        break;
      default:
        break;
    }
  }
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
      case sf::Keyboard::A:
      case sf::Keyboard::D:
        tank->rotate_body(Rotation::None);
        break;
      case sf::Keyboard::Left:
      case sf::Keyboard::Right:
        tank->rotate_tower(Rotation::None);
        break;
      case sf::Keyboard::W:
      case sf::Keyboard::S:
        tank->set_gear(Gear::Neutral);
        break;
      default:
        break;
    }
  }
}
