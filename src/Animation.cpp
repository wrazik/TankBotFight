#include "Animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

Animation::Animation(const std::string& file_name, int frame_count, double animation_time,
                     sf::Vector2f position, TextureStore& store)
    : mPosition(position), mStore(store) {
  for (int i = 1; i <= frame_count; ++i) {
    mAnimationFiles.push_back(file_name + std::to_string(i) + ".png");
  }
  mDeltaTime = animation_time / frame_count;
}
void Animation::draw(sf::RenderWindow& render_window) {
  auto elapsed_time = mClock.getElapsedTime();

  if (elapsed_time.asMilliseconds() > mDeltaTime) {
    mClock.restart();
    mCurrentFrame++;
    if (mCurrentFrame >= mAnimationFiles.size()) {
      mIsDrawingFinished = true;
      return;
    }
  }
  sf::Sprite sprite;
  sprite.setTexture(mStore.get().get_texture(mAnimationFiles[mCurrentFrame]));
  sprite.setPosition(mPosition - sf::Vector2f{sprite.getGlobalBounds().width / 2,
                                              sprite.getGlobalBounds().height / 2});
  render_window.draw(sprite);
}
