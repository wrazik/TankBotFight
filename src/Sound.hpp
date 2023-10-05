#pragma once
#include <SFML/Audio.hpp>
#include <string>

#include "Files.hpp"

class Sound {
 private:
  // sound data is not stored directly in sf::Sound, it is stored in sf::SoundBuffer
  sf::SoundBuffer mBuffer;

  // load Sound from file (it can be loaded from memory, stream, array of samples, which are 16 bit
  // integers with sign) MP3 is not supproted due to licensing
  std::string mPath;

  // to play a sound, sf::Sound instance is needed.
  sf::Sound mSound;


 public:
  Sound();
  Sound(const Sound& sound);
  Sound& operator=(const Sound& sound);
  
  Sound(std::string file_name);
  ~Sound();
  void play();
  bool load_from_file(std::string file_name);
  void set_buffer();

};
