#include "TextureStore.hpp"

#include <utility>

#include "Files.hpp"

sf::Texture& TextureStore::get_texture(const std::string& path, const sf::IntRect& area) {
  if (!mStore.contains(path)) {
    sf::Texture t;
    if (!t.loadFromFile(files::default_size_path() + path, area)) {
      throw std::runtime_error(std::string("Texture ") + path + " not found");
    }
    mStore.insert(std::make_pair(path, std::move(t)));
  }
  return mStore[path];
}
