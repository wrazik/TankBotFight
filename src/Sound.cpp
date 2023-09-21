#include "Sound.hpp"

Sound::Sound(std::string file_name) {
  if (load_from_file(file_name)) {
    set_buffer();
  }
}

Sound::~Sound() {
  // nothing to do here
}

void Sound::play() { mSound.play(); }

bool Sound::load_from_file(std::string file_name) {
  std::string path_to_file = files::asset_path() + "/res/Sound/" + file_name;

  return mBuffer.loadFromFile(path_to_file);
}

void Sound::set_buffer() { mSound.setBuffer(mBuffer); }
