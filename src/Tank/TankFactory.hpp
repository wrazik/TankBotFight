#pragma once
#include <Tank/Tank.hpp>

class TextureStore;
class TankFactory {
 public:
  [[nodiscard]] static Tank Random(TextureStore& store, float x, float y);
};
