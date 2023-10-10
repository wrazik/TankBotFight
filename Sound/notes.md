SFML provides two classes for playing audio: sf::Sound and sf::Music. They both provide more or less the same features, the main difference is how they work. 

sf::Sound is a lightweight object that plays loaded audio data from a sf::SoundBuffer. It should be used for small sounds that can fit in memory and should suffer no lag when they are played. Examples are gun shots, foot steps, etc. 

sf::Music doesn't load all the audio data into memory, instead it streams it on the fly from the source file. It is typically used to play compressed music that lasts several minutes, and would otherwise take many seconds to load and eat hundreds of MB in memory.
