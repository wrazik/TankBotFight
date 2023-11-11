#include "Button.hpp"

Button::Button(std::string text, sf::Vector2f top_left_corner, unsigned int width,
               unsigned int height, void (*callback)(void), ButtonType button_type,
               MenuLevel* next_level)
    : mTextContent{text},
      mCallback{callback},
      MenuItem{top_left_corner},
      mWidth{width},
      mHeight{height},
      mButtonType{button_type},
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
  rectangle.setPosition(mPosition);
  window.draw(rectangle);

  // center text
  mText.setOrigin(mText.getGlobalBounds().getSize() / 2.f + mText.getLocalBounds().getPosition());
  mText.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));
  window.draw(mText);
}

void Button::select() { mIsSelected = true; }

void Button::deselect() { mIsSelected = false; }

void Button::click() {
  if (mButtonType == ButtonType::Callback && mIsSelected) {
    mCallback();
  }
}

ButtonType Button::get_button_type() const { return mButtonType; }

MenuLevel* Button::get_next_level() const { return mNextLevel; }
