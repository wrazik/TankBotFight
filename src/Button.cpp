#include "Button.hpp"

Button::Button(std::string text, void (*callback)(void), Button_type button_type)
    : mText{text}, mCallback{callback}, mButtonType{button_type} {}

bool Button::is_clicked(const sf::Event& event){};