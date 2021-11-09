#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Drawable.hpp"

class Trace : public sf::Drawable {
  sf::Transform mTransform;
  sf::VertexArray mVertices{sf::Quads, 4};
  const sf::Texture& mTexture;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 public:
  Trace(const sf::Texture& tex, const sf::Vector2f& pos, const float angle, const float start_height);
  void increase_height(const float amount);
  void decrease_height(const float amount);
};
