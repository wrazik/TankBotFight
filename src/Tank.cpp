//
//  Tank.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//
#include "Tank.hpp"

#include "Direction.hpp"
#include "Files.hpp"
#include <filesystem>
#include <stdexcept>

Tank::Tank(int x, int y, float speed)
  : mSpeed(speed)
{
  if (!txt.loadFromFile(files::default_size_path() + "tank_green.png")) {
    throw std::runtime_error("Cannot a read graphic file!");
  }
  sprite.setTexture(txt);
  sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

  sprite.setPosition(static_cast<float>(x), static_cast<float>(y));

  sprite.scale(0.1f, 0.1f);
}

void
Tank::move(Direction direction)
{

  switch (direction) {
    case Direction::Up:
      sprite.move(0.f, -mSpeed);
      break;
    case Direction::Down:
      sprite.move(0.f, mSpeed);
      break;
    case Direction::Left:
      sprite.move(-mSpeed, 0.f);
      break;
    case Direction::Right:
      sprite.move(mSpeed, 0.f);
      break;
  }
}

sf::Sprite&
Tank::getSprite()
{
  return sprite;
}
