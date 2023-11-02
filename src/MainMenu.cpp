#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window, std::initializer_list<MenuLevel*> menu_level_ptrs,
                   MenuLevel* current_level)
    : mWindow{window}, mMenuLevelPtrs{menu_level_ptrs}, mCurrentLevel{current_level} {}

void MainMenu::process_and_draw(const sf::Event& event) {
  // process inputs
  mCurrentLevel->draw(mWindow, event);

  // draw menu

  // perform actions
}
