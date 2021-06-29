#pragma once
#include <background/Ground.hpp>
#include <optional>
#include <string>

class BackgroundTextureName {
 public:
  using GroundTypeVec = std::vector<std::vector<GroundType>>;

  static std::string get(const GroundTypeVec& v, int x, int y);

 private:
  static std::optional<GroundType> get_elem(const GroundTypeVec& v, int x, int y);
  static std::string get_road(const GroundTypeVec& v, int x, int y);
  static std::string get_surface(const GroundTypeVec& v, int x, int y);
  static std::array<std::optional<GroundType>, 4> get_neighbors(const GroundTypeVec& v, int x,
                                                                int y);
  static bool is_vertical_road(const GroundTypeVec& v, int x, int y);
  static bool is_horizontal_road(const GroundTypeVec& v, int x, int y);
  static bool is_x_crossroad(const GroundTypeVec& v, int x, int y);
  static bool is_t_crossroad(const GroundTypeVec& v, int x, int y);
};
