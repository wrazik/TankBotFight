#pragma once
#include <background/Ground.hpp>
#include <string>

class BackgroundTextureName {
 public:
  using GroundTypeVec = std::vector<std::vector<GroundType>>;

  static std::string get(const GroundTypeVec& v, int x, int y);

 private:
  static std::string get_road(const GroundTypeVec& v, int x, int y);
  static std::string get_surface(const GroundTypeVec& v, int x, int y);
};
