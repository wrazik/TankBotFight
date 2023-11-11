#pragma once

#include <string>
#include <vector>

#include "Button.hpp"

class Button;

class MenuLevel {
 public:
  MenuLevel(std::initializer_list<Button> buttons);
  void draw(sf::RenderWindow&, const sf::Font& font);
  void processEvents(const sf::Event& event);
  bool is_level_change_requested() const;
  MenuLevel* get_next_level() const;
  void reset_level_request();

 private:
  std::vector<Button> mButtons;
  int mSelectedButton = 0;
  bool mIsClicked = false;
  bool mRequestLevelChange = false;
  MenuLevel* mNextLevel;
};