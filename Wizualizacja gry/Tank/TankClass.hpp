//
//  TankClass.hpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#ifndef TankClass_hpp
#define TankClass_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "ResourcePath.hpp"

class Tank {
    
    int hp = 0;
    int dmg = 0;
    int spd = 0;
    
    sf::Texture txt;
    sf::Sprite sprite;
    
public:
    
    Tank(int x, int y);
    
    void move(std::string direction);
    
    void dead(bool heIsDead_QuestionMark);
    
    sf::Sprite getSprite();
    
};

#endif /* TankClass_hpp */
