#include "background/SurfaceGenerator.hpp"
#include "background/FillVec.hpp"
#include "Random.hpp"
#include "Size.hpp"

SurfaceGenerator::SurfaceVec SurfaceGenerator::generate() {
  SurfaceGenerator::SurfaceVec surface_types(FIELDS_HEIGHT);
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    surface_types[i] = std::vector(FIELDS_WIDTH, Surface::Grass);
  }

  SurfacePattern pattern = static_cast<SurfacePattern>(random_range(0, SurfacePattern::Size));

  switch(pattern) {
      case SurfacePattern::VerticalSandGrass: {
          const int column = random_range(0, FIELDS_WIDTH - 1);
          fill_vec(surface_types, 0, column, FIELDS_HEIGHT, FIELDS_WIDTH, Surface::Sand);
          break;
      }
      case SurfacePattern::VerticalGrassSand: {
          const int column = random_range(0, FIELDS_WIDTH - 1);
          fill_vec(surface_types, 0, 0, FIELDS_HEIGHT, column, Surface::Sand);
          break;
      }
      case SurfacePattern::HorizontalSandGrass: {
          const int row = random_range(0, FIELDS_HEIGHT - 1);
          fill_vec(surface_types, 0, 0, row, FIELDS_WIDTH, Surface::Sand);
          break;
      }
      case SurfacePattern::HorizontalGrassSand: {
          const int row = random_range(0, FIELDS_HEIGHT - 1);
          fill_vec(surface_types, row, 0, FIELDS_HEIGHT, FIELDS_WIDTH, Surface::Sand);
          break;
      }
  }
  return surface_types;
}
