#include "Button.hpp"

Button::Button(std::string text, point_t top_left_corner, unsigned int width, unsigned int height,
               void (*callback)(void), MenuLevel* next_level)
    : mTextContent{text},
      mCallback{callback},
      MenuItem{top_left_corner},
      mWidth{width},
      mHeight{height},
      mNextLevel{next_level} {}

void Button::draw(sf::RenderWindow& window, const sf::Font& font) {
  // draw rectangle
  sf::RectangleShape rectangle(sf::Vector2f(mWidth, mHeight));

  // draw rectangle outline
  if (mIsSelected) {
    rectangle.setOutlineThickness(10.0f);
    rectangle.setOutlineColor(sf::Color(255, 0, 0));
  } else {
    rectangle.setOutlineThickness(0.0f);
  }

  // set text
  mText.setFont(font);
  mText.setCharacterSize(24);
  mText.setColor(sf::Color::Red);
  mText.setString(mTextContent);

  // move objects in window and draw
  rectangle.move(mPosition);
  window.draw(rectangle);
  mText.move(mPosition);
  window.draw(mText);
}

void Button::select() { mIsSelected = true; }

void Button::deselect() { mIsSelected = false; }
