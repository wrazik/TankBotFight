#include "MainMenu.hpp"

#include "Files.hpp"

MainMenu::MainMenu(sf::RenderWindow& window, std::initializer_list<MenuLevel*> menu_level_ptrs,
                   MenuLevel* current_level)
    : mWindow{window}, mMenuLevelPtrs{menu_level_ptrs}, mCurrentLevel{current_level} {
  mFont.loadFromFile(files::asset_path() + "DejaVuSans.ttf");
}

void MainMenu::process_and_draw(const sf::Event& event) {
  // process inputs
  mCurrentLevel->processEvents(event);

  // draw menu
  mCurrentLevel->draw(mWindow, mFont);

  // perform actions
}
