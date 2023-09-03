#pragma once

#include <memory>

#include "Controllers/KeyboardController.hpp"
#include "Tank/Tank.hpp"

namespace sf {
class Event;
class RenderWindow;
}  // namespace sf

class Board;

class KeyboardPlayer {
 public:
  KeyboardPlayer(Board& board, std::unique_ptr<Tank>&& tank);

  void draw(sf::RenderWindow& window);
  void handle_events(const sf::Event& event);
  void update();
  bool take_hit(unsigned int damage);

  [[nodiscard]] const Tank& get_tank() const;

 private:
  Board& mBoard;
  std::unique_ptr<Tank> mTank;
  std::unique_ptr<KeyboardController> mController;
};
