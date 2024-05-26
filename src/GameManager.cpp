#include "GameManager.hpp"

#include "Size.hpp"

// define static variables
bool GameManager::request_state_change = false;
GameManagerState GameManager::desired_state = GameManagerState::InvalidState;

// Button callbacks:
void main_menu_start_callback(void) {
  GameManager::request_state_change = true;
  GameManager::desired_state = GameManagerState::Started;
}
void main_menu_exit_callback(void) {
  GameManager::request_state_change = true;
  GameManager::desired_state = GameManagerState::Exit;
}

// define menus
extern MenuLevel options;

const unsigned int buttonWidth = WIDTH / 5;
const unsigned int buttonHeight = HEIGHT / 10;
constexpr unsigned int verticalSpacing = 20;

MenuLevel main_menu{
    {{"Start", sf::Vector2f((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 1),
      buttonWidth, buttonHeight, main_menu_start_callback, ButtonType::Callback, nullptr},
     {"Options", sf::Vector2f((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 3),
      buttonWidth, buttonHeight, nullptr, ButtonType::LevelChanger, &options},
     {"Exit", sf::Vector2f((WIDTH - buttonWidth) / 2, verticalSpacing + buttonHeight * 5),
      buttonWidth, buttonHeight, main_menu_exit_callback, ButtonType::Callback, nullptr}}};

MenuLevel options{{"Back", sf::Vector2f(WIDTH / 2 - buttonWidth, 2 * buttonHeight + 20),
                   buttonWidth, buttonHeight, nullptr, ButtonType::LevelChanger, &main_menu}};

GameManager::GameManager()
    : mWindow{sf::VideoMode(WIDTH, HEIGHT), "TankBotFight"},
      mBoard{mWindow},
      mMainMenu{mWindow, {&main_menu, &options}, &main_menu} {}

void GameManager::start() {
  while (mWindow.isOpen()) {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
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

void GameManager::performStateMachine(const sf::Event& event) {
  switch (mGameManagerState) {
    case GameManagerState::MainMenu:
      mMainMenu.process_and_draw(event);
      break;
    case GameManagerState::Started:
      mBoard.play(event);
      break;
    case GameManagerState::Exit:
      mWindow.close();
      break;
  }

  // check if state change is requested
  if (request_state_change) {
    request_state_change = false;
    transitState();
  }
}

void GameManager::transitState() {
  switch (mGameManagerState) {
    case GameManagerState::MainMenu:
      if (desired_state == GameManagerState::Started) {
        mGameManagerState = GameManagerState::Started;
      } else if (desired_state == GameManagerState::Exit) {
        mGameManagerState = GameManagerState::Exit;
      }
      break;
    case GameManagerState::Started:
      // TODO -> pause game
      break;
  }
}
