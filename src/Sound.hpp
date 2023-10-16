#pragma once
#include <SFML/Audio.hpp>
#include <string>

#include "Files.hpp"

class Sound {
 private:
  sf::SoundBuffer mBuffer;
  sf::Sound mSound;

 public:
  Sound(Sound&&) noexcept = default;
  Sound& operator=(Sound&&) noexcept = default;

  Sound(const Sound& sound) = delete;
  Sound& operator=(const Sound& sound) = delete;

  explicit Sound(const std::string& file_name);
  void play();
};
