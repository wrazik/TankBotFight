#include "Sound.hpp"

Sound::Sound(const Sound& sound) {
  mBuffer = sound.mBuffer;
  mSound = sound.mSound;
  mSound.setBuffer(mBuffer);
}

Sound::Sound(const std::string& file_name) {
  if (load_from_file(file_name)) {
    mSound.setBuffer(mBuffer);
  } else {
    throw std::runtime_error("couldn't load sound");
  }
}

void Sound::play() { mSound.play(); }

bool Sound::load_from_file(std::string file_name) {
  std::string path_to_file = files::asset_path() + "Sounds/" + file_name;

  return mBuffer.loadFromFile(path_to_file);
}
