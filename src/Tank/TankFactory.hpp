#pragma once
#include <memory>

class TextureStore;
class Tank;
class TankFactory {
 public:
  [[nodiscard]] static std::unique_ptr<Tank> Random(TextureStore& store, float x, float y);
};
