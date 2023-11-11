#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Engine.hpp"

KeyboardController::KeyboardController(Tank& tank, Board& board) : mTank(tank), mBoard(board) {}

void KeyboardController::update(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      case sf::Keyboard::A:
        mTank.rotate_body(Rotation::Counterclockwise);
        mTank.rotate_turret(Rotation::Counterclockwise);
        break;
      case sf::Keyboard::D:
        mTank.rotate_body(Rotation::Clockwise);
        mTank.rotate_turret(Rotation::Clockwise);
        break;
      case sf::Keyboard::Left:
        mTank.rotate_turret(Rotation::Counterclockwise);
        break;
      case sf::Keyboard::Right:
        mTank.rotate_turret(Rotation::Clockwise);
        break;
      case sf::Keyboard::W:
        mTank.set_gear(Gear::Drive);
        break;
      case sf::Keyboard::S:
        mTank.set_gear(Gear::Reverse);
        break;
      case sf::Keyboard::Space:
        if (const auto& missile = mTank.shoot()) {
          mBoard.register_missile(missile.value());
        }
        break;
      default:
        break;
    }
  }
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
      case sf::Keyboard::A:
      case sf::Keyboard::D:
        mTank.rotate_body(Rotation::None);
        mTank.rotate_turret(Rotation::None);
        break;
      case sf::Keyboard::Left:
      case sf::Keyboard::Right:
        mTank.rotate_turret(Rotation::None);
        break;
      case sf::Keyboard::W:
      case sf::Keyboard::S:
        mTank.set_gear(Gear::Neutral);
        break;
      default:
        break;
    }
  }
}
