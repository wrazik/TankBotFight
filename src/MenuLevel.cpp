#include "MenuLevel.hpp"

MenuLevel::MenuLevel(std::initializer_list<Button> buttons) : mButtons{buttons} {}

void MenuLevel::processEvents(const sf::Event& event) {
  // process keyboard inputs
  static sf::Keyboard::Key lastPressedKey;
  if (event.type == sf::Event::KeyPressed) {
    if (lastPressedKey != event.key.code) {
      if (event.key.code == sf::Keyboard::Up) {
        mSelectedButton--;
        if (mSelectedButton < 0) {
          mSelectedButton = mButtons.size() - 1;
        }
      }

      if (event.key.code == sf::Keyboard::Down) {
        mSelectedButton++;
        if (mSelectedButton >= mButtons.size()) {
          mSelectedButton = 0;
        }
      }

      if (event.key.code == sf::Keyboard::Enter) {
        if (mButtons.size()) {
          if (mButtons[mSelectedButton].get_button_type() == ButtonType::Callback) {
            mButtons[mSelectedButton].click();
          } else if (mButtons[mSelectedButton].get_button_type() == ButtonType::LevelChanger) {
            mNextLevel = mButtons[mSelectedButton].get_next_level();
            mRequestLevelChange = true;
          }
        }
      }
    }

    lastPressedKey = event.key.code;
  } else if (event.type == sf::Event::KeyReleased) {
    lastPressedKey = sf::Keyboard::Unknown;
  }

  // process button selection
  for (int i = 0; i < mButtons.size(); ++i) {
    if (i == mSelectedButton) {
      mButtons[i].select();
    } else {
      mButtons[i].deselect();
    }
  }
}

bool MenuLevel::is_level_change_requested() const { return mRequestLevelChange; }

MenuLevel* MenuLevel::get_next_level() const { return mNextLevel; }

void MenuLevel::reset_level_request() { mRequestLevelChange = false; }

void MenuLevel::draw(sf::RenderWindow& window, const sf::Font& font) {
  for (auto& button : mButtons) {
    button.draw(window, font);
  }
}
