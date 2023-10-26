#include "MenuLevel.hpp"

MenuLevel::MenuLevel(std::initializer_list<Button> buttons, MenuLevel* prevLevel = nullptr)
    : mButtons{buttons}, mPrevLevel{prevLevel} {}