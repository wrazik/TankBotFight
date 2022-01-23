#pragma once
#include <Tank.hpp>
#include <TextureStore.hpp>

class TankFactory {
 public:
  static Tank Random(TextureStore& store, float x, float y);
};