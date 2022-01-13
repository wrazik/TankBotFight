#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

#include "Size.hpp"

constexpr inline double to_radians(double degrees) { return PI / 180.f * degrees; }
constexpr inline double to_degrees(double radians) { return radians / PI * 180; }
inline sf::Vector2f fabs(const sf::Vector2f& vec) { return {std::fabs(vec.x), std::fabs(vec.y)}; }
inline float hypot(const sf::Vector2f& vec) { return std::hypot(vec.x, vec.y); }

inline bool equal(float lhs, float rhs, float precision = 0.001f) {
  return std::fabs(lhs - rhs) < precision;
}

inline bool equal(const sf::Vector2f& lhs, const sf::Vector2f& rhs, float precision = 0.001f) {
  return equal(lhs.x, rhs.x, precision) && equal(lhs.y, rhs.y, precision);
}

inline void print_rect(const auto& rect) {
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

inline bool is_sprite_x_in_board(const float x, const sf::Sprite& sp) {
  const float sp_left_x_offset = fabs(sp.getOrigin().x - sp.getLocalBounds().left);
  const float sp_right_x_offset =
      fabs(sp.getOrigin().x - (sp.getLocalBounds().left + sp.getLocalBounds().width));
  return x > sp_left_x_offset && x < WIDTH - sp_right_x_offset;
}

inline bool is_sprite_y_in_board(const float y, const sf::Sprite& sp) {
  const float sp_top_y_offset = fabs(sp.getOrigin().y - sp.getLocalBounds().top);
  const float sp_bot_y_offset =
      fabs(sp.getOrigin().y - (sp.getLocalBounds().top + sp.getLocalBounds().height));
  return y > sp_top_y_offset && y < HEIGHT - sp_bot_y_offset;
}

inline float get_opposite_angle(const float angle) {
  float opposite_angle = angle - 180.f;
  if (opposite_angle < 0.f) {
    opposite_angle = 360.f + opposite_angle;
  }
  return opposite_angle;
}
