#include "Button.hpp"

Button::Button(std::string text, point_t top_left_corner, unsigned int width, unsigned int height,
               void (*callback)(void), MenuLevel* next_level)
    : mText{text},
      mCallback{callback},
      MenuItem{top_left_corner},
      mWidth{width},
      mHeight{height},
      mNextLevel{next_level} {}

bool Button::is_clicked(const sf::Event& event) {}

void Button::draw(sf::RenderWindow& window) {
  sf::RectangleShape rectangle(sf::Vector2f(mWidth, mHeight));

  if (mIsSelected) {
    rectangle.setOutlineThickness(10.0f);
    rectangle.setOutlineColor(sf::Color(255, 0, 0));
  } else {
    rectangle.setOutlineThickness(0.0f);
  }
  rectangle.move(mPosition);
  window.draw(rectangle);
}

void Button::select() { mIsSelected = true; }

void Button::deselect() { mIsSelected = false; }