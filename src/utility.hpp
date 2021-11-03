#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

#include "Size.hpp"

constexpr inline double to_radians(double degrees) { return pi / 180.f * degrees; }
constexpr inline double to_degrees(double radians) { return radians / pi * 180; }
inline sf::Vector2f fabs(const sf::Vector2f& vec) { return {std::fabs(vec.x), std::fabs(vec.y)}; }
inline float hypot(const sf::Vector2f& vec) { return std::hypot(vec.x, vec.y); }

inline bool equal(float lhs, float rhs, float precision = 0.001f) {
  return std::fabs(lhs - rhs) < precision;
}

inline bool equal(const sf::Vector2f& lhs, const sf::Vector2f& rhs, float precision = 0.001f) {
  return equal(lhs.x, rhs.x, precision) && equal(lhs.y, rhs.y, precision);
}

inline void printRect(const auto& rect) {
  const auto& [x, y, width, height] = rect;
  std::cout << "(x, y): (" << x << ", " << y << ") - (w x h): (" << width << " x " << height
            << ")\n";
}

inline void print_point(const auto& point) {
  const auto& [x, y] = point;
  std::cout << "(x, y): (" << x << ", " << y << ")\n";
}

inline float get_angle(const sf::Vector2f& vec) {
  if (equal(vec.x, 0.f) && equal(vec.y, 0.f)) {
    return 0.f;
  }
  auto degrees = to_degrees(atan2(vec.y, vec.x)) + 90;
  if (degrees < 0) {
    return 360 + degrees;
  }
  return degrees;
}
