#pragma once

#include <string>
#include <vector>

#include "Button.hpp"

class Button;

class MenuLevel {
  std::vector<Button> mButtons;
  MenuLevel* mPrevLevel;
  int mSelectedButton = 0;

 public:
  MenuLevel(std::initializer_list<Button> buttons);
  void draw(sf::RenderWindow&, const sf::Font& font);
  void processEvents(const sf::Event& event);
};