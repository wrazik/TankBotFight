#include "TestUtility.hpp"

#include <gtest/gtest.h>

void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
  const auto [x1, y1] = lhs;
  const auto [x2, y2] = rhs;
  EXPECT_NEAR(x1, x2, 0.0001);
  EXPECT_NEAR(y1, y2, 0.0001);
}

std::unique_ptr<sf::Texture> create_dummy_texture(unsigned int width, unsigned int height) {
  auto dummy = std::make_unique<sf::Texture>();
  dummy->create(width, height);
  return dummy;
}
