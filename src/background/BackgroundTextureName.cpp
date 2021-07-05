#include "background/BackgroundTextureName.hpp"

#include <Random.hpp>
#include <Size.hpp>
#include <array>
#include <optional>

using namespace std::string_literals;

std::string BackgroundTextureName::get(const GroundTypeVec& v, int x, int y) {
  if (v[x][y].mIsRoad) return get_road(v, x, y);
  return get_surface(v, x, y);
}

std::optional<GroundType> BackgroundTextureName::get_elem(const GroundTypeVec& v, int x, int y) {
  if (x >= 0 && y >= 0 && x < v.size() && y < v[0].size()) {
    return v[x][y];
  }
  return std::nullopt;
}

std::array<std::optional<GroundType>, 4> BackgroundTextureName::get_neighbors(
    const GroundTypeVec& v, int x, int y) {
  return {get_elem(v, x, y - 1), get_elem(v, x + 1, y), get_elem(v, x - 1, y),
          get_elem(v, x, y + 1)};
}

bool BackgroundTextureName::is_t_crossroad(const GroundTypeVec& v, int x, int y) {
  const auto [left, down, up, right] = get_neighbors(v, x, y);

  // clang-format off
  return (
      (down && down->mIsRoad) && 
      (left && left->mIsRoad) &&
      (right && right->mIsRoad)
    );
  // clang-format on
}

bool BackgroundTextureName::is_x_crossroad(const GroundTypeVec& v, int x, int y) {
  const auto [left, down, up, right] = get_neighbors(v, x, y);

  // clang-format off
  return 
    (!right || right->mIsRoad) && 
    (!left || left->mIsRoad) &&  
    (!up || up->mIsRoad) && 
    (!down || down->mIsRoad);
  // clang-format on
}

bool BackgroundTextureName::is_vertical_road(const GroundTypeVec& v, int x, int y) {
  const auto [left, down, up, right] = get_neighbors(v, x, y);

  // clang-format off
  return 
    (!right || !right->mIsRoad) && 
    (!left || !left->mIsRoad) &&  
    (!up || up->mIsRoad) && 
    (!down || down->mIsRoad);
  // clang-format on
}

bool BackgroundTextureName::is_horizontal_road(const GroundTypeVec& v, int x, int y) {
  const auto [left, down, up, right] = get_neighbors(v, x, y);
  // clang-format off
  return 
    (!up || !up->mIsRoad) && 
    (!down || !down->mIsRoad) && 
    (!left || left->mIsRoad) &&
    (!right || right->mIsRoad);
  // clang-format on
}

std::string BackgroundTextureName::get_road(const GroundTypeVec& v, int x, int y) {
  std::string texture_name = "tile";
  const auto& me = v[x][y];
  const auto [left, up, down, right] = get_neighbors(v, x, y);
  if (v[x][y].mSurface == SurfaceType::Sand) {
    texture_name += "Sand_road"s;
  } else {
    texture_name += "Grass_road"s;
  }

  if (is_x_crossroad(v, x, y)) {
    return texture_name + one_of("CrossingRound.png"s, "Crossing.png"s);
  } else if (is_t_crossroad(v, x, y)) {
    return texture_name + "SplitS.png"s;
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
  if (is_vertical_road(v, x, y)) {
    return texture_name + "North.png";
  } else if (is_horizontal_road(v, x, y)) {
    return texture_name + "East.png";
  }
  throw std::runtime_error("Not recognized background pattern");
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
