#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "MenuLevel.hpp"

using point_t = sf::Vector2u;

class Button {
  std::string mText;
  MenuLevel* mNextLevel;
  point_t mTopLeft;
  unsigned int mWidth;
  unsigned int mHeight;

  void (*mCallback)(void);

 public:
  Button(std::string text, void (*callback)(void), MenuLevel* nextLevel = nullptr);

  bool is_clicked(const sf::Event& event);
};