#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "MenuItem.hpp"
#include "MenuLevel.hpp"

using point_t = sf::Vector2f;

class MenuLevel;

class Button : MenuItem {
  std::string mTextContent;
  sf::Text mText;
  unsigned int mWidth;
  unsigned int mHeight;
  void (*mCallback)(void);
  bool mIsSelected = false;
  MenuLevel* mNextLevel;

 public:
  Button(std::string text, point_t top_left_corner, unsigned int width, unsigned int height,
         void (*callback)(void), MenuLevel* next_level = nullptr);
  void draw(sf::RenderWindow& window, const sf::Font& font);
  void select();
  void deselect();
};