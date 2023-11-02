#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.hpp"
#include "MenuLevel.hpp"

class MainMenu {
 public:
  MainMenu(sf::RenderWindow& window, std::initializer_list<MenuLevel*> menu_level_ptrs,
           MenuLevel* current_level);

  void process_and_draw(const sf::Event& event);

 private:
  sf::RenderWindow& mWindow;
  std::vector<MenuLevel*> mMenuLevelPtrs;
  MenuLevel* mCurrentLevel = nullptr;
  sf::Font mFont;
};