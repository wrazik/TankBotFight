#include "Button.hpp"

Button::Button(std::string text, void (*callback)(void), Button_type button_type,
               MenuLevel* next_level)
    : mText{text}, mCallback{callback}, mButtonType{button_type}, mNextLevel{next_level} {}

bool Button::is_clicked(const sf::Event& event){};