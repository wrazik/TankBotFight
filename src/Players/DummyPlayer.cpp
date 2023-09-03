#include "DummyPlayer.hpp"

#include "SFML/Graphics.hpp"

DummyPlayer::DummyPlayer(Board& board, std::unique_ptr<Tank>&& tank)
    : mBoard(board),
      mTank(std::move(tank)),
      mController(std::make_unique<DummyController>(*mTank, mBoard)) {}

void DummyPlayer::draw(sf::RenderWindow& window) { mTank->draw(window); }

void DummyPlayer::update() {
  mController->update();
  mTank->update();
}

bool DummyPlayer::take_hit(unsigned int damage) { return mTank->take_hit(damage); }

const Tank& DummyPlayer::get_tank() const { return *mTank; }
