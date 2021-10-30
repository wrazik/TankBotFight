#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <range/v3/view/iota.hpp>

inline constexpr double precision{0.0001};
void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
std::unique_ptr<sf::Texture> create_dummy_texture(uint = 5, uint = 5);

template <typename T>
concept Updatable = requires(T a) {
  a.update();
};

void update_many(Updatable auto& updatable, int count) {
  for (int i : ranges::iota_view(0, count)) {
    updatable.update();
  }
}
