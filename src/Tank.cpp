//
//  Tank.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#include "Tank.hpp"
#include "Direction.hpp"
#include <stdexcept>

Tank::Tank(int x, int y, int speed)
  : mSpeed(speed)
{
  if (!txt.loadFromFile("../res/tamiya-135-us-medium-tank-m4-sherman-early-production.jpg")) {
    throw std::runtime_error("Cannot read graphic file!");
  }
  sprite.setTexture(txt);
  sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

  sprite.setPosition(x, y);

  sprite.scale(0.1, 0.1);
}

void
Tank::move(Direction direction)
{

  switch (direction) {
    case Direction::Up:
      sprite.move(0, -mSpeed);
      break;
    case Direction::Down:
      sprite.move(0, mSpeed);
      break;
    case Direction::Left:
      sprite.move(-mSpeed, 0);
      break;
    case Direction::Right:
      sprite.move(mSpeed, 0);
      break;
  }
}

sf::Sprite&
Tank::getSprite()
{
  return sprite;
}
