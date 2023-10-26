#include "MainMenu.h"

void main_menu_start_callback(void) { std::cout << "Start clicked!\n"; }
void main_menu_options_callback(void) { std::cout << "Options clicked!\n"; }
void main_menu_exit_callback(void) { std::cout << "Exit clicked!\n"; }

void options_back_callback(void) { std::cout << "Options: back clicked\n"; }

// button -> text, callback, clickable, nextLevel

extern MenuLevel options;

MenuLevel main_menu{{{"Start", main_menu_start_callback, Button_type::Clickable},
                     {"Options", main_menu_options_callback, Button_type::Clickable},
                     {"Exit", main_menu_exit_callback, Button_type::Clickable}}};

MenuLevel options{{"Back", options_back_callback, Button_type::Clickable}};

MainMenu::MainMenu(sf::Window& window, std::initializer_list<MenuLevel*> menu_level_ptrs,
                   MenuLevel* current_level)
    : mWindow{window}, mCurrentLevel{current_level} {}

void MainMenu::process_and_draw(const sf::Event& event) {
  // process inputs

  // draw menu

  // perform actions
}
