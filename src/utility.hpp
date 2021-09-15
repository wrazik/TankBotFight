#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Size.hpp"

constexpr inline float to_radians(float degrees) { return pi / 180.f * degrees; }
inline sf::Vector2f abs(const sf::Vector2f& vec) { return {std::abs(vec.x), std::abs(vec.y)}; }
inline float hypot(const sf::Vector2f& vec) { return std::hypot(vec.x, vec.y); }
inline sf::Vector2f get_pos(const sf::Vector2f& start, float move_distance, float move_angle) {
    
}
