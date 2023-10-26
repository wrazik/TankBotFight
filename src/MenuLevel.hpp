#pragma once

#include <string>
#include <vector>

#include "Button.hpp"

class Button;

class MenuLevel {
  std::vector<Button> mButtons;
  MenuLevel* mPrevLevel;

 public:
  MenuLevel(std::initializer_list<Button> buttons);
};