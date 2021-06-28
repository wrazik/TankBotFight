#include <gtest/gtest.h>

#include <background/BackgroundTextureName.hpp>
#include <string>
using namespace std::string_literals;

struct BackgroundTextureNameTests : ::testing::Test {
  using Vec = BackgroundTextureName::GroundTypeVec;
  Vec mVec;

  std::string get_name() { return BackgroundTextureName::get(mVec, 1, 1); }
};

inline constexpr auto SAND = GroundType{SurfaceType::Sand, false};
inline constexpr auto SAND_ROAD = GroundType{SurfaceType::Sand, true};
inline constexpr auto GRASS = GroundType{SurfaceType::Grass, false};
inline constexpr auto GRASS_ROAD = GroundType{SurfaceType::Grass, true};

using BackgroundSurfaceTest = BackgroundTextureNameTests;

TEST_F(BackgroundSurfaceTest, SurfaceSand_ShouldReturnSand) {
  mVec = {
      {SAND, SAND, SAND},
      {SAND, SAND, SAND},
      {SAND, SAND, SAND},
  };
  const auto generated = get_name();
  EXPECT_TRUE(generated == "tileSand1.png" || generated == "tileSand2.png");
}

TEST_F(BackgroundSurfaceTest, SurfaceGrass_ShouldReturnGrass) {
  mVec = {
      {GRASS, GRASS, GRASS},
      {GRASS, GRASS, GRASS},
      {GRASS, GRASS, GRASS},
  };
  const auto generated = get_name();
  EXPECT_TRUE(generated == "tileGrass1.png" || generated == "tileGrass2.png");
}

TEST_F(BackgroundSurfaceTest, SurfaceVerticalGrassToSand) {
  mVec = {
      {GRASS, SAND, SAND},
      {GRASS, SAND, SAND},
      {GRASS, SAND, SAND},
  };
  EXPECT_EQ(get_name(), "tileGrass_transitionE.png"s);
}

TEST_F(BackgroundSurfaceTest, SurfaceVerticalSandToGrass) {
  mVec = {
      {SAND, SAND, GRASS},
      {SAND, SAND, GRASS},
      {SAND, SAND, GRASS},
  };
  EXPECT_EQ(get_name(), "tileGrass_transitionW.png"s);
}

TEST_F(BackgroundSurfaceTest, SurfaceHorizontalSandToGrass) {
  mVec = {
      {SAND, SAND, SAND},
      {SAND, SAND, SAND},
      {GRASS, GRASS, GRASS},
  };
  EXPECT_EQ(get_name(), "tileGrass_transitionN.png"s);
}

TEST_F(BackgroundSurfaceTest, SurfaceHorizontalGrassToSand) {
  mVec = {
      {GRASS, GRASS, GRASS},
      {SAND, SAND, SAND},
      {SAND, SAND, SAND},
  };
  EXPECT_EQ(get_name(), "tileGrass_transitionS.png"s);
}

using BackgroundRoadTest = BackgroundTextureNameTests;

TEST_F(BackgroundRoadTest, VerticalGrass) {
  mVec = {
      {GRASS, GRASS, GRASS},
      {GRASS_ROAD, GRASS_ROAD, GRASS_ROAD},
      {GRASS, GRASS, GRASS},
  };
  EXPECT_EQ(get_name(), "tileGrass_roadEast.png"s);
}

TEST_F(BackgroundRoadTest, HorizontalGrass) {
  mVec = {
      {GRASS, GRASS_ROAD, GRASS},
      {GRASS, GRASS_ROAD, GRASS},
      {GRASS, GRASS_ROAD, GRASS},
  };
  EXPECT_EQ(get_name(), "tileGrass_roadNorth.png"s);
}

TEST_F(BackgroundRoadTest, VerticalSand) {
  mVec = {
      {SAND, SAND, SAND},
      {SAND_ROAD, SAND_ROAD, SAND_ROAD},
      {SAND, SAND, SAND},
  };
  EXPECT_EQ(get_name(), "tileSand_roadEast.png"s);
}

TEST_F(BackgroundRoadTest, HorizontalSand) {
  mVec = {
      {SAND, SAND_ROAD, SAND},
      {SAND, SAND_ROAD, SAND},
      {SAND, SAND_ROAD, SAND},
  };
  EXPECT_EQ(get_name(), "tileSand_roadNorth.png"s);
}

TEST_F(BackgroundRoadTest, VerticalSandToGrass) {
  mVec = {
      {SAND, SAND, SAND},
      {GRASS_ROAD, SAND_ROAD, SAND_ROAD},
      {SAND, SAND, SAND},
  };
  const auto name = get_name();
  EXPECT_TRUE(name == "tileGrass_roadTransitionE.png"s ||
              name == "tileGrass_roadTransitionE_dirt.png"s);
}

TEST_F(BackgroundRoadTest, VerticalGrassToSand) {
  mVec = {
      {SAND, SAND, SAND},
      {SAND_ROAD, SAND_ROAD, GRASS_ROAD},
      {SAND, SAND, SAND},
  };
  const auto name = get_name();
  EXPECT_TRUE(name == "tileGrass_roadTransitionW.png"s ||
              name == "tileGrass_roadTransitionW_dirt.png"s);
}

TEST_F(BackgroundRoadTest, HorizontalGrassToSand) {
  mVec = {
      {SAND, GRASS_ROAD, SAND},
      {SAND, SAND_ROAD, SAND},
      {SAND, SAND_ROAD, SAND},
  };
  const auto name = get_name();
  EXPECT_TRUE(name == "tileGrass_roadTransitionS.png"s ||
              name == "tileGrass_roadTransitionS_dirt.png"s);
}

TEST_F(BackgroundRoadTest, HorizontalSandToGrass) {
  mVec = {
      {SAND, SAND_ROAD, SAND},
      {SAND, SAND_ROAD, SAND},
      {SAND, GRASS_ROAD, SAND},
  };
  const auto name = get_name();
  EXPECT_TRUE(name == "tileGrass_roadTransitionN.png"s ||
              name == "tileGrass_roadTransitionN_dirt.png"s);
}
