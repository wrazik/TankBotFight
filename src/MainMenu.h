#pragma once
#include <SFML/Graphics.hpp>

// Item: Level
// Level --> Items
// Level contain items. each item contain pointer to next and previous level

// MainMenu: Start, Options, Exit
// Start: --> start game
// Options --> back.
// Exit --> exit.

void main_menu_start_callback(void) { std::cout << "Start clicked!\n"; }
void main_menu_options_callback(void) { std::cout << "Options clicked!\n"; }
void main_menu_exit_callback(void) { std::cout << "Exit clicked!\n"; }

extern LevelOfMenu options;

// menu objects
LevelOfMenu main_menu{{
                          {"Start", main_menu_start_callback, nullptr},
                          {"Options", main_menu_options_callback, &options},
                          {"Exit" main_menu_exit_callback, nullptr},
                      },
                      nullptr};

void options_back_callback(void){std::cout << "Options: back clicked\n"}

LevelOfMenu options{{"Back", options_back_callback}, &main_menu};

class MainMenu {
 public:
  MainMenu(sf::Window& window, std::initializer_list<LevelOfMenu*> menuLevelPtrs,
           LevelOfMenu* currentLevel = nullptr)
      : mWindow{window}, mCurrentLevel{currentLevel} {}

  void process_and_draw(const sf::Event& event);

 private:
  sf::Window& mWindow;
  std::vector<LevelOfMenu*> mMenuLevelPtrs;
  LevelOfMenu* mCurrentLevel = nullptr;
};