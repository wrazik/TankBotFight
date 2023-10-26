#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "MenuLevel.hpp"

using point_t = sf::Vector2u;

enum class Button_type { Clickable, Not_clickable };

class MenuLevel;

class Button {
  std::string mText;
  point_t mTopLeft;
  unsigned int mWidth;
  unsigned int mHeight;
  void (*mCallback)(void);
  MenuLevel* mNextLevel;
  Button_type mButtonType;

 public:
  Button(std::string text, void (*callback)(void),
         Button_type button_type = Button_type::Not_clickable);
  bool is_clicked(const sf::Event& event);
};