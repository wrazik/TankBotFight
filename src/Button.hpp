#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "MenuItem.hpp"
#include "MenuLevel.hpp"

enum class ButtonType { Callback, LevelChanger };

class MenuLevel;

class Button : MenuItem {
 public:
  Button(std::string text, sf::Vector2f top_left_corner, unsigned int width, unsigned int height,
         void (*callback)(void), ButtonType button_type, MenuLevel* next_level = nullptr);
  void draw(sf::RenderWindow& window, const sf::Font& font);
  void select();
  void deselect();
  void click();
  ButtonType get_button_type() const;
  MenuLevel* get_next_level() const;

 private:
  std::string mTextContent;
  sf::Text mText;
  unsigned int mWidth;
  unsigned int mHeight;
  void (*mCallback)(void);
  bool mIsSelected = false;
  MenuLevel* mNextLevel;
  ButtonType mButtonType;
};