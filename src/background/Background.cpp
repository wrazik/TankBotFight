#include "Background.hpp"

#include <random>
#include <string>

#include "Files.hpp"
#include "Size.hpp"

using namespace std::string_literals;
Background::Background(TextureStore& store) : mTextureStore(store), mGround(FIELDS_HEIGHT) {
  auto ground_types = SurfaceGenerator::generate();
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    for (int j = 0; j < FIELDS_WIDTH; ++j) {
      mGround[i].emplace_back(get_texture(ground_types, i, j));
    }
  }
}

sf::Texture& Background::get_texture(const Background::GroundTypeVec& v, int x, int y) {
  if (v[x][y] == Surface::Sand) {
    if (x - 1 > 0 && v[x - 1][y] == Surface::Grass) {
      return mTextureStore.get_texture("tileGrass_transitionS.png");
    } else if (y - 1 > 0 && v[x][y - 1] == Surface::Grass) {
      return mTextureStore.get_texture("tileGrass_transitionE.png");
    } else if (x + 1 < FIELDS_HEIGHT && v[x + 1][y] == Surface::Grass) {
      return mTextureStore.get_texture("tileGrass_transitionN.png");
    } else if (y + 1 < FIELDS_WIDTH && v[x][y + 1] == Surface::Grass) {
      return mTextureStore.get_texture("tileGrass_transitionW.png");
    }
    return mTextureStore.get_texture(one_of("tileSand1.png"s, "tileSand2.png"s));
  }
  return mTextureStore.get_texture(one_of("tileGrass1.png"s, "tileGrass2.png"s));
}

void Background::draw(sf::RenderWindow& window) {
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    for (int j = 0; j < FIELDS_WIDTH; ++j) {
      mGround[i][j].draw(window, j * GROUND_HEIGHT, i * GROUND_WIDTH);
    }
  }
}
