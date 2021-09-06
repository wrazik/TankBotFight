#pragma once
#include <SFML/System/Vector2.hpp>
#include <ranges>

#include "Engine.hpp"
#include "Tank.hpp"

void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

template <typename T>
concept Updatable = requires(T a) {
  a.update();
};

void update_many(Updatable auto& updatable, int count) {
  for (int i : std::ranges::iota_view{0, count}) {
    updatable.update();
  }
}
