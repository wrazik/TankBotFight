#pragma once
#include "Ground.hpp"
#include "TextureStore.hpp"

inline constexpr int WIDTH = 1024;
inline constexpr int HEIGHT = 768;

class Background
{
public:
  Background(sf::RenderWindow& window);

  void draw();

private:
  using GroundTypeVec = std::vector<std::vector<GroundType>>;
  using GroundVec = std::vector<std::vector<Ground>>;
  static std::vector<std::vector<GroundType>> generate_random_ground();
  static void fill_with_sand(GroundTypeVec& ground_types,
                             int start_x,
                             int start_y,
                             int end_x,
                             int end_y);
  sf::Texture& get_texture(const GroundTypeVec& v, int x, int y);

  inline static constexpr int M_WIDTH = WIDTH / GROUND_WIDTH;
  inline static constexpr int M_HEIGHT = HEIGHT / GROUND_HEIGHT;
  TextureStore mTextureStore;
  sf::RenderWindow& mWindow;
  GroundVec mGround;
};
