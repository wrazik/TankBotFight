#include "GameManager.hpp"

#include "Size.hpp"

void main_menu_start_callback(void) { std::cout << "Start clicked!\n"; }
void main_menu_options_callback(void) { std::cout << "Options clicked!\n"; }
void main_menu_exit_callback(void) { std::cout << "Exit clicked!\n"; }

void options_back_callback(void) { std::cout << "Options: back clicked\n"; }

// button -> text, callback, clickable, nextLevel

extern MenuLevel options;

const unsigned int buttonWidth = WIDTH / 5;
const unsigned int buttonHeight = HEIGHT / 10;
constexpr unsigned int verticalSpacing = 20;

MenuLevel main_menu{
    {{"Start", point_t((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 1), buttonWidth,
      buttonHeight, main_menu_start_callback, nullptr},
     {"Options", point_t((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 3),
      buttonWidth, buttonHeight, main_menu_options_callback, &options},
     {"Exit", point_t((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 5), buttonWidth,
      buttonHeight, main_menu_exit_callback, nullptr}}};

MenuLevel options{{"Back", point_t(WIDTH / 2 - buttonWidth, 2 * buttonHeight + 20), buttonWidth,
                   buttonHeight, options_back_callback, &main_menu}};

GameManager::GameManager()
    : mWindow{sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"},
      mBoard{mWindow},
      mMainMenu{mWindow, {&main_menu, &options}, &main_menu} {}

void GameManager::start() {
  while (mWindow.isOpen()) {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (mWindow.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        mGameManagerState = GameManagerState::Exit;
      }
      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        mGameManagerState = GameManagerState::Exit;
      }
    }

    // clear the window with black color
    mWindow.clear(sf::Color::Black);

    performStateMachine(event);

    // end the current frame
    mWindow.display();
  }
}
#include <iostream>
void GameManager::performStateMachine(const sf::Event& event) {
  switch (mGameManagerState) {
    case GameManagerState::MainMenu:
      mMainMenu.process_and_draw(event);
      /*
      [this]() {
        std::string input;
        std::cout << "Welcome to the game!\n";
        std::cout << "1. Play\n2. Exit\nSelect: ";
        std::cin >> input;
        switch (input[0]) {
          case '1':
            mGameManagerState = GameManagerState::Started;
            break;
          case '2':
            mGameManagerState = GameManagerState::Exit;
            break;
        }
      }();
      */
      break;
    case GameManagerState::Started:
      mBoard.play(event);
      break;
    case GameManagerState::Exit:
      mWindow.close();
      break;
  }
}
