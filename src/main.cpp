
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

//SFML Libraries
#include <SFML/Graphics.hpp>

//My Libraries
#include "TankClass.hpp"
#include "ObstacleClass.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TankBotFight");

    window.setFramerateLimit(1);
    
    Tank tankA(400, 300);
    
    Obstacle obstracleA(100, 100);
    
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        window.clear();
        window.draw(tankA.getSprite());
        window.draw(obstracleA.getSprite());
        window.display();
    }

    return EXIT_SUCCESS;
}
