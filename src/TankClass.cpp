//
//  TankClass.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#include "TankClass.hpp"

Tank::Tank(int x, int y, int speed) {
    if(!txt.loadFromFile("tamiya-135-us-medium-tank-m4-sherman-early-production.jpg")) {
        return 0;
    }
    sprite.setTexture(txt);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    
    sprite.setPosition(x, y);
    
    sprite.scale(0.1, 0.1);
    
    spd = speed;
    
}

void Tank::move(Direction direction) {
    
    if(direction == Direction::Up) {
        sprite.move(0, -sprite.getGlobalBounds().height);
    }
    
    if(direction == Direction::Down) {
        sprite.move(0, sprite.getGlobalBounds().height);
    }
    
    if(direction == Direction::Right) {
        sprite.move(sprite.getGlobalBounds().height, 0);
    }
    
    if(direction == Direction::Left) {
        sprite.move(-sprite.getGlobalBounds().height, 0);
    }
    
}

sf::Sprite& Tank::getSprite() {
    return sprite;
}
