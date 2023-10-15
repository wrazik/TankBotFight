#pragma once
#include <memory>

class TextureStore;
class Tank;
class Sound;

class TankFactory {
 public:
  [[nodiscard]] static std::unique_ptr<Tank> Random(TextureStore& store, float x, float y,
                                                    const Sound& shot_sound);
};
