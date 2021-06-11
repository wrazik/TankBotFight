//
//  ObstacleClass.hpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#ifndef ObstacleClass_hpp
#define ObstacleClass_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "ResourcePath.hpp"

class Obstacle {
    
    sf::Texture txt;
    sf::Sprite sprite;
    
public:
    Obstacle(int x, int y);
    
    sf::Sprite getSprite();
  
};

#endif /* ObstacleClass_hpp */
