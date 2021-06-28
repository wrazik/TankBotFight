#include "Background.hpp"

#include <background/BackgroundTextureName.hpp>
#include <background/RoadGenerator.hpp>
#include <optional>
#include <random>
#include <string>

#include "Files.hpp"
#include "Size.hpp"

using namespace std::string_literals;
Background::Background(TextureStore& store) : mTextureStore(store), mGround(FIELDS_HEIGHT) {
  const auto surface_types = SurfaceGenerator::generate();
  const auto road_types = RoadGenerator::generate();
  std::vector<std::vector<GroundType>> grounds(FIELDS_HEIGHT);
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    for (int j = 0; j < FIELDS_WIDTH; ++j) {
      grounds[i].emplace_back(surface_types[i][j], road_types[i][j]);
    }
  }

  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    for (int j = 0; j < FIELDS_WIDTH; ++j) {
      mGround[i].emplace_back(mTextureStore.get_texture(get_texture_name(grounds, i, j)));
    }
  }
}

void Background::draw(sf::RenderWindow& window) {
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    for (int j = 0; j < FIELDS_WIDTH; ++j) {
      mGround[i][j].draw(window, j * GROUND_HEIGHT, i * GROUND_WIDTH);
    }
  }
}

std::string Background::get_texture_name(const GroundTypeVec& v, int x, int y) {
  return BackgroundTextureName::get(v, x, y);
}
