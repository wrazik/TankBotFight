#include "RoadGenerator.hpp"
#include "Random.hpp"
#include "Size.hpp"
#include "FillVec.hpp"

RoadGenerator::RoadVec RoadGenerator::generate_random_road() {
    const auto pattern = static_cast<RoadPattern>(random_range(0, RoadPattern::Size));
    RoadGenerator::RoadVec road_vec(FIELDS_HEIGHT);
    for (int i = 0; i < FIELDS_HEIGHT; ++i) {
      road_vec[i] = std::vector(FIELDS_WIDTH, false);
    }

    switch(pattern) {
        case VerticalLine: {
            const auto row = random_range(1, FIELDS_HEIGHT-2);
            fill_vec(road_vec, 0, row, FIELDS_WIDTH - 1, row, false);
            break;
       }
        default:
            break;
    }
    return road_vec;
}

