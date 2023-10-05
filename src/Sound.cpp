#include "Sound.hpp"

Sound::Sound() { /* empty */ }

Sound::Sound(const Sound& sound){
  mBuffer = sound.mBuffer;
  mSound = sound.mSound;
  set_buffer();
}

Sound::Sound(std::string file_name) {
  if (load_from_file(file_name)) {
    set_buffer();
  }
}

Sound& Sound::operator=(const Sound& sound)
{
  mBuffer = sound.mBuffer;
  mSound = sound.mSound;
  set_buffer();
  return *this;
}

Sound::~Sound() {
  // nothing to do here
}

void Sound::play() { mSound.play(); }

bool Sound::load_from_file(std::string file_name) {
  std::string path_to_file = files::asset_path() + "Sounds/" + file_name;

  return mBuffer.loadFromFile(path_to_file);
}

void Sound::set_buffer() { mSound.setBuffer(mBuffer); }
