#pragma once

#include <memory>

#include "Controllers/DummyController.hpp"
#include "Tank/Tank.hpp"

namespace sf {
class Event;
class RenderWindow;
}  // namespace sf

class Board;

class DummyPlayer {
 public:
  DummyPlayer(Board& board, std::unique_ptr<Tank>&& tank);

  void draw(sf::RenderWindow& window);
  void update();

  [[nodiscard]] const Tank& get_tank() const;
  [[nodiscard]] Tank& get_tank();

 private:
  Board& mBoard;
  std::unique_ptr<Tank> mTank;
  std::unique_ptr<DummyController> mController;
};
