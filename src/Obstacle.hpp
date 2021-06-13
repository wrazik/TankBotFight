//
//  ObstacleClass.hpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

class Obstacle
{

public:
  Obstacle(int x, int y);

  sf::Sprite getSprite();

private:
  sf::Texture txt;
  sf::Sprite sprite;
};
