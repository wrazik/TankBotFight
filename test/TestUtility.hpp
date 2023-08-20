#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <iterator>
#include <memory>

inline constexpr double PRECISION{0.0001};
void expect_vec2f_eq(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

template <typename T>
void expect_vec_eq(const std::vector<T>& lhs, const std::vector<T>& rhs) {
  ASSERT_EQ(lhs.size(), rhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    EXPECT_EQ(lhs[i], rhs[i]);
  }
}

template <typename Iter>
  requires std::input_iterator<Iter>
std::vector<std::iter_value_t<Iter>> dereference_vec(const std::vector<Iter>& vec) {
  std::vector<std::iter_value_t<Iter>> result{};
  for (const auto& iter : vec) {
    result.push_back(*iter);
  }
  return result;
}

std::unique_ptr<sf::Texture> create_dummy_texture(unsigned int = 5, unsigned int = 5);

template <typename T>
concept Updatable = requires(T a) { a.update(); };

void update_many(Updatable auto& updatable, int count) {
  for (int i = 0; i < count; ++i) {
    updatable.update();
  }
}
