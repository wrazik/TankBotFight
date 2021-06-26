#pragma once
#include "background/Ground.hpp"


enum SurfacePattern {
    VerticalSandGrass = 0,
    VerticalGrassSand,
    HorizontalSandGrass,
    HorizontalGrassSand,
    Size
};

class SurfaceGenerator {
public:
  using SurfaceVec = std::vector<std::vector<Surface>>;

  static SurfaceVec generate();
};
