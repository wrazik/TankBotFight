#include "background/BackgroundTextureName.hpp"

#include <Random.hpp>
#include <Size.hpp>
#include <optional>

using namespace std::string_literals;

std::string BackgroundTextureName::get(const GroundTypeVec& v, int x, int y) {
  if (v[x][y].mIsRoad) return get_road(v, x, y);
  return get_surface(v, x, y);
}

std::string BackgroundTextureName::get_road(const GroundTypeVec& v, int x, int y) {
  std::string texture_name = "tile";
  auto get_elem = [&v](const int x, const int y) -> std::optional<GroundType> {
    if (x >= 0 && y >= 0 && x < FIELDS_HEIGHT - 1 && y < FIELDS_WIDTH - 1) {
      return v[x][y];
    }
    return std::nullopt;
  };
  const auto& me = v[x][y];
  const auto left = get_elem(x, y - 1);
  const auto up = get_elem(x + 1, y);
  const auto down = get_elem(x - 1, y);
  const auto right = get_elem(x, y + 1);
  if (v[x][y].mSurface == SurfaceType::Sand) {
    texture_name += "Sand_road";
  } else {
    texture_name += "Grass_road";
  }

  if (me.mSurface == SurfaceType::Sand) {
    if (left && left->mIsRoad && left->mSurface == SurfaceType::Grass) {
      return "tileGrass_road"s + one_of("TransitionE.png"s, "TransitionE_dirt.png"s);
    } else if (right && right->mIsRoad && right->mSurface == SurfaceType::Grass) {
      return "tileGrass_road"s + one_of("TransitionW.png"s, "TransitionW_dirt.png"s);
    } else if (up && up->mIsRoad && up->mSurface == SurfaceType::Grass) {
      return "tileGrass_road"s + one_of("TransitionN.png"s, "TransitionN_dirt.png"s);
    } else if (down && down->mIsRoad && down->mSurface == SurfaceType::Grass) {
      return "tileGrass_road"s + one_of("TransitionS.png"s, "TransitionS_dirt.png"s);
    }
  }
  if ((!right || !right->mIsRoad) && (!left || !left->mIsRoad)) {
    if ((!up || up->mIsRoad) && (!down || down->mIsRoad)) texture_name += "North.png";
  } else if ((!up || !up->mIsRoad) && (!down || !down->mIsRoad)) {
    if ((!left || left->mIsRoad) && (!right || right->mIsRoad)) texture_name += "East.png";
  }

  return texture_name;
}

std::string BackgroundTextureName::get_surface(const GroundTypeVec& v, int x, int y) {
  if (v[x][y].mSurface == SurfaceType::Sand) {
    if (x - 1 >= 0 && v[x - 1][y].mSurface == SurfaceType::Grass) {
      return "tileGrass_transitionS.png"s;
    } else if (y - 1 >= 0 && v[x][y - 1].mSurface == SurfaceType::Grass) {
      return "tileGrass_transitionE.png"s;
    } else if (x + 1 < FIELDS_HEIGHT && v[x + 1][y].mSurface == SurfaceType::Grass) {
      return "tileGrass_transitionN.png"s;
    } else if (y + 1 < FIELDS_WIDTH && v[x][y + 1].mSurface == SurfaceType::Grass) {
      return "tileGrass_transitionW.png";
    }
    return one_of("tileSand1.png"s, "tileSand2.png"s);
  }
  return one_of("tileGrass1.png"s, "tileGrass2.png"s);
}
