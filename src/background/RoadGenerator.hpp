#pragma once
#include "Ground.hpp"
#include <SFML/Graphics.hpp>

class TextureStore;

class RoadGenerator{
public:
  using RoadVec = std::vector<std::vector<bool>>;
  using GroundTypeVec = std::vector<std::vector<GroundType>>;

  static RoadVec generate_random_road();

};

enum RoadPattern {
    /* * * * *
     - - - - -
     * * * * *
     * * * * *
     * * * * */
    VerticalLine = 0,
//    /* * * | *
//     * * * | *
//     * * * | *
//     * * * | *
//     * * * | */
//    HorizontalLine,
//    /* * * | *
//     - - - + -
//     * * * | *
//     * * * | *
//     * * * | */
//    SingleCrossroad,
//    /* * | * *
//     * * | * *
//     * * | * *
//     * * L - -
//     * * * * */
//    UpperRight,
//    UpperLeft,
//    LowerRight,
//    LowerLeft,
//    /* * * * *
//     - - - - -
//     * * | * *
//     * * | * *
//     * * | * */
//    LetterT,
//    /* * | * *
//     * * | * *
//     - - - - -
//     * * * * *
//     * * * * */
//    ReversedT
    Size
};
