#include "SurfaceGenerator.hpp"

#include <Random.hpp>
#include <Size.hpp>
#include <background/FillVec.hpp>

SurfaceGenerator::SurfaceVec SurfaceGenerator::generate() {
  SurfaceGenerator::SurfaceVec surface_types(FIELDS_HEIGHT);
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    surface_types[i] = std::vector(FIELDS_WIDTH, SurfaceType::Grass);
  }

  const auto pattern =
      static_cast<SurfacePattern::Pattern>(random_range(0, SurfacePattern::Size - 1));

  switch (pattern) {
    case SurfacePattern::VerticalSandGrass: {
      const int column = random_range(2, FIELDS_WIDTH - 3);
      fill_vec(surface_types, 0, column, FIELDS_HEIGHT - 1, FIELDS_WIDTH - 1, SurfaceType::Sand);
      break;
    }
    case SurfacePattern::VerticalGrassSand: {
      const int column = random_range(2, FIELDS_WIDTH - 3);
      fill_vec(surface_types, 0, 0, FIELDS_HEIGHT - 1, column, SurfaceType::Sand);
      break;
    }
    case SurfacePattern::HorizontalSandGrass: {
      const int row = random_range(2, FIELDS_HEIGHT - 3);
      fill_vec(surface_types, 0, 0, row, FIELDS_WIDTH - 1, SurfaceType::Sand);
      break;
    }
    case SurfacePattern::HorizontalGrassSand: {
      const int row = random_range(2, FIELDS_HEIGHT - 3);
      fill_vec(surface_types, row, 0, FIELDS_HEIGHT - 1, FIELDS_WIDTH - 1, SurfaceType::Sand);
      break;
    }
  }
  return surface_types;
}
