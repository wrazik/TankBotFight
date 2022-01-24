#include "SFML/Graphics.hpp"

class Trace : public sf::Drawable {
  sf::Transform mTransform;
  sf::VertexArray mVertices{sf::Quads, 4};
  const sf::Texture& mTexture;
  float mRotation;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
  Trace(const sf::Texture& tex, const sf::Vector2f& pos, float angle, float start_height);
  void increase_height(float amount);
  void decrease_height(float amount);
  [[nodiscard]] float get_height() const;
  [[nodiscard]] float get_rotation() const;
};
