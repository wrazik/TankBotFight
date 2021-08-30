#include "Board.hpp"

int main() {
  Board b;
  b.register_tank();
  b.register_enemy_tank();
  b.run();
  return 0;
}
