#include "Button.hpp"

Button::Button(std::string text, void (*callback)(void), LevelOfMenu* nextLevel = nullptr)
    : mText{text}, mCallback{callback}, mNextLevel{nextLevel} {}

bool Button::is_clicked(const sf::Event& event){};