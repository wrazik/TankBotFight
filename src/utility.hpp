#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <gsl/gsl>
#include <iostream>
#include <iterator>

#include "Size.hpp"

[[nodiscard]] constexpr inline double to_radians(double degrees) { return PI / 180.f * degrees; }
[[nodiscard]] constexpr inline double to_degrees(double radians) { return radians / PI * 180; }
[[nodiscard]] inline sf::Vector2f fabs(const sf::Vector2f& vec) {
  return {std::fabs(vec.x), std::fabs(vec.y)};
}
[[nodiscard]] inline float hypot(const sf::Vector2f& vec) { return std::hypot(vec.x, vec.y); }

[[nodiscard]] inline bool equal(float lhs, float rhs, float precision = 0.001f) {
  return std::fabs(lhs - rhs) < precision;
}

[[nodiscard]] inline bool equal(const sf::Vector2f& lhs, const sf::Vector2f& rhs,
                                float precision = 0.001f) {
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

[[nodiscard]] inline float get_angle(const sf::Vector2f& vec) {
  if (equal(vec, {0.f, 0.f})) {
    return 0.f;
  }
  auto degrees = gsl::narrow_cast<float>(to_degrees(atan2(vec.y, vec.x))) + 90;
  if (degrees < 0) {
    return 360 + degrees;
  }
  return degrees;
}

[[nodiscard]] inline bool is_sprite_x_in_board(const float x, const sf::Sprite& sp) {
  const auto sp_left_x_offset = fabs(sp.getOrigin().x - sp.getLocalBounds().left);
  const auto sp_right_x_offset =
      fabs(sp.getOrigin().x - (sp.getLocalBounds().left + sp.getLocalBounds().width));
  return x > sp_left_x_offset && x < WIDTH - sp_right_x_offset;
}

[[nodiscard]] inline bool is_sprite_y_in_board(const float y, const sf::Sprite& sp) {
  const auto sp_top_y_offset = fabs(sp.getOrigin().y - sp.getLocalBounds().top);
  const auto sp_bot_y_offset =
      fabs(sp.getOrigin().y - (sp.getLocalBounds().top + sp.getLocalBounds().height));
  return y > sp_top_y_offset && y < HEIGHT - sp_bot_y_offset;
}

[[nodiscard]] inline float get_opposite_angle(const float angle) {
  float opposite_angle = angle - 180.f;
  if (opposite_angle < 0.f) {
    opposite_angle = 360.f + opposite_angle;
  }
  return opposite_angle;
}

[[nodiscard]] inline sf::Vector2f get_center_of_rect(const sf::FloatRect& rect) {
  return sf::Vector2f {rect.left + rect.width / 2.f, rect.top + rect.height / 2.f};
}
