#include "KeyboardController.hpp"

#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Tank.hpp"

KeyboardController::KeyboardController(Tank& tank, Board& board) : mTank(tank), mBoard(board) {
  mLastShot = std::chrono::system_clock::now();
}

void KeyboardController::update(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
    mTank.rotate_body(Rotation::Counterclockwise);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
    mTank.rotate_body(Rotation::None);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
    mTank.rotate_body(Rotation::Clockwise);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) {
    mTank.rotate_body(Rotation::None);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
    mTank.rotate_tower(Rotation::Counterclockwise);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) {
    mTank.rotate_tower(Rotation::None);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
    mTank.rotate_tower(Rotation::Clockwise);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) {
    mTank.rotate_tower(Rotation::None);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
    mTank.set_current_speed(5);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W) {
    mTank.set_current_speed(0);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
    mTank.set_current_speed(-5);
  }
  if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
    mTank.set_current_speed(0);
  }
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
    const auto now = std::chrono::system_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - mLastShot);
    if (elapsed >= std::chrono::milliseconds{500}) {
      mLastShot = now;
      mBoard.fire_missle(mTank.get_tower_rotation(), mTank.get_position().x,
                         mTank.get_position().y);
    }
  }
}
