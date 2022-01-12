//
//  Obstacle.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#include "Obstacle.hpp"

#include <stdexcept>

Obstacle::Obstacle(int x, int y) {
  if (!mTxt.loadFromFile("../res/przeszkoda-obedience.jpg")) {
    throw std::runtime_error("Cannot read graphic file!");
  }
  mSprite.setTexture(mTxt);
  mSprite.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);

  mSprite.setPosition(static_cast<float>(x), static_cast<float>(y));

  constexpr float SCALE_FACTOR = 0.1f;
  mSprite.scale(SCALE_FACTOR, SCALE_FACTOR);
}

sf::Sprite Obstacle::get_sprite() { return mSprite; }
