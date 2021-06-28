#include "RoadGenerator.hpp"

#include "FillVec.hpp"
#include "Random.hpp"
#include "Size.hpp"

RoadGenerator::RoadVec RoadGenerator::generate() {
  const auto pattern = static_cast<RoadPattern::Pattern>(random_range(0, RoadPattern::Size - 1));
  RoadGenerator::RoadVec road_vec(FIELDS_HEIGHT);
  for (int i = 0; i < FIELDS_HEIGHT; ++i) {
    road_vec[i] = std::vector(FIELDS_WIDTH, false);
  }

  switch (pattern) {
    case RoadPattern::VerticalLine: {
      const auto column = random_range(2, FIELDS_WIDTH - 2);
      fill_vec(road_vec, 0, column, FIELDS_HEIGHT - 1, column, true);
      break;
    }
    case RoadPattern::HorizontalLine: {
      const auto row = random_range(2, FIELDS_HEIGHT - 2);
      fill_vec(road_vec, row, 0, row, FIELDS_WIDTH - 1, true);
      break;
    }
    default:
      break;
  }
  return road_vec;
}
