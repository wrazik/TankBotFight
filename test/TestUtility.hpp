#pragma once
#include <SFML/System/Vector2.hpp>
#include "Engine.hpp"
#include "Tank.hpp"

void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
float to_radians(float degrees);

template <typename Updatable>
void update_many(Updatable& updatable, int count) {
  for (int i = 0; i < count; i++) {
    updatable.update();
  }
}
