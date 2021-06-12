//
//  TankClass.hpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Direction.hpp"

class Tank
{
    
public:
    
    Tank(int x, int y, int speed);
    
    void move(Direction direction);
    
    void dead();
    
    sf::Sprite& getSprite();
    
private:
    
    int hp = 0;
    int dmg = 0;
    int spd = 0;
    
    sf::Texture txt;
    sf::Sprite sprite;
    
};
