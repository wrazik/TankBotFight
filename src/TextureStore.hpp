#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureStore {
 public:
  TextureStore() = default;
  TextureStore(TextureStore&) = delete;
  TextureStore& operator=(TextureStore&) = delete;
  TextureStore(TextureStore&&) = delete;
  TextureStore& operator=(TextureStore&&) = delete;
  ~TextureStore() = default;

  sf::Texture& get_texture(const std::string& file);

 private:
  std::unordered_map<std::string, sf::Texture> mStore;
};
