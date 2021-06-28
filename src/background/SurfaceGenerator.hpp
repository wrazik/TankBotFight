#pragma once
#include <background/Ground.hpp>

namespace SurfacePattern {
enum Pattern {
  VerticalSandGrass = 0,
  VerticalGrassSand,
  HorizontalSandGrass,
  HorizontalGrassSand,
  Size
};
}

class SurfaceGenerator {
 public:
  using SurfaceVec = std::vector<std::vector<SurfaceType>>;

  static SurfaceVec generate();
};
