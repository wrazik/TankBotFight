//
//  ObstacleClass.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#include "ObstacleClass.hpp"

Obstacle::Obstacle(int x, int y) {
    if(!txt.loadFromFile("przeszkoda-obedience.jpg")) {
        return 0;
    }
    sprite.setTexture(txt);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    
    sprite.setPosition(x, y);
    
    sprite.scale(0.1, 0.1);
    
}

sf::Sprite Obstacle::getSprite() {
    return sprite;
}
