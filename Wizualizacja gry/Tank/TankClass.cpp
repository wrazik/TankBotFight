//
//  TankClass.cpp
//  TankBotFight
//
//  Created by Emil Panecki on 10/06/2021.
//  Copyright © 2021 Emil Panecki. All rights reserved.
//

#include "TankClass.hpp"

Tank::Tank(int x, int y) {
    txt.loadFromFile(resourcePath() + "tamiya-135-us-medium-tank-m4-sherman-early-production.jpg");
    sprite.setTexture(txt);
    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
    
    sprite.setPosition(x, y);
    
    sprite.scale(0.1, 0.1);
    
}

void Tank::move(std::string direction) {
    
    if(direction == "up") {
        sprite.move(0, -sprite.getGlobalBounds().height);
    }
    
    if(direction == "down") {
        sprite.move(0, sprite.getGlobalBounds().height);
    }
    
    if(direction == "right") {
        sprite.move(sprite.getGlobalBounds().height, 0);
    }
    
    if(direction == "left") {
        sprite.move(-sprite.getGlobalBounds().height, 0);
    }
    
}

sf::Sprite Tank::getSprite() {
    return sprite;
}
