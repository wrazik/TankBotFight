#include "Sound.hpp"

#include <iostream>

Sound::Sound(const std::string& file_name) {
  std::string path_to_file = files::asset_path() + "Sounds/" + file_name;
  if (!mBuffer.loadFromFile(path_to_file)) {
    throw std::runtime_error("couldn't load sound");
  }
}

void Sound::play() {
  mSound.setBuffer(mBuffer);
  mSound.play();
}