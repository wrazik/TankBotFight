#pragma once
#include <SFML/Audio.hpp>
#include <string>

#include "Files.hpp"

class Sound {
 private:
  // sound data is not stored directly in sf::Sound, it is stored in sf::SoundBuffer
  sf::SoundBuffer mBuffer;

  // to play a sound, sf::Sound instance is needed.
  sf::Sound mSound;

 public:
  Sound(const Sound& sound);

  Sound(const std::string& file_name);
  void play();
  bool load_from_file(std::string file_name);
};
