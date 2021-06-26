#pragma once
#include <vector>

#include "Ground.hpp"
#include "Random.hpp"
#include "TextureStore.hpp"
#include "background/SurfaceGenerator.hpp"

class Background {
 public:
  Background(TextureStore& texture_store);

  void draw(sf::RenderWindow& mWindow);

 private:
  using GroundTypeVec = std::vector<std::vector<Surface>>;
  using GroundVec = std::vector<std::vector<Ground>>;
  static std::vector<std::vector<GroundType>> generate_random_ground();
  static void fill_with_sand(GroundTypeVec& ground_types, int start_x, int start_y, int end_x,
                             int end_y);
  sf::Texture& get_texture(const GroundTypeVec& v, int x, int y);

  TextureStore& mTextureStore;
  GroundVec mGround;
};
