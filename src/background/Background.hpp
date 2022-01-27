#pragma once
#include <Random.hpp>
#include <TextureStore.hpp>
#include <background/Ground.hpp>
#include <background/SurfaceGenerator.hpp>
#include <string>
#include <vector>

class Background {
 public:
  explicit Background(TextureStore& texture_store);

  void draw(sf::RenderWindow& mWindow);

 private:
  using SurfaceVec = std::vector<std::vector<SurfaceType>>;
  using GroundTypeVec = std::vector<std::vector<GroundType>>;
  using GroundVec = std::vector<std::vector<Ground>>;

  TextureStore& mTextureStore;
  GroundVec mGround;
};
