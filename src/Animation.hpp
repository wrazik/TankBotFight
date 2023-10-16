#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>

#include "TextureStore.hpp"

class Animation {
 public:
  Animation(const std::string& file_name, int frame_count, double animation_time,
            sf::Vector2f position, TextureStore& store);
  void draw(sf::RenderWindow& render_window);
  bool is_finished() const { return mIsDrawingFinished; }

  Animation(const Animation&) = delete;
  Animation& operator=(const Animation&) = delete;
  Animation(Animation&&) = default;
  Animation& operator=(Animation&&) = default;

 private:
  std::vector<std::string> mAnimationFiles;
  int mCurrentFrame = 0;
  bool mIsDrawingFinished = false;
  double mDeltaTime = 0;
  sf::Clock mClock;
  sf::Vector2f mPosition;
  std::reference_wrapper<TextureStore> mStore;
};
