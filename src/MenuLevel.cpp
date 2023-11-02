#include "MenuLevel.hpp"

MenuLevel::MenuLevel(std::initializer_list<Button> buttons) : mButtons{buttons} {}

void MenuLevel::processEvents(const sf::Event& event) {
  // process input
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
    }

    lastPressedKey = event.key.code;
  } else if (event.type == sf::Event::KeyReleased) {
    lastPressedKey = sf::Keyboard::Unknown;
  }
}

void MenuLevel::draw(sf::RenderWindow& window, const sf::Font& font) {
  // select button - draw outline
  for (int i = 0; i < mButtons.size(); ++i) {
    if (i == mSelectedButton) {
      mButtons[i].select();
    } else {
      mButtons[i].deselect();
    }
  }

  // draw buttons
  for (auto& button : mButtons) {
    button.draw(window, font);
  }
}
