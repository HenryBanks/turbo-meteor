//
//  Enemy.hpp
//  Test SFML
//
//  Created by Henry Banks on 13/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "Projectiles.hpp"
#include <random>
#include "Ship.hpp"

class Enemy{
public:
    Enemy();
    Enemy(float xPos, float yPos);
    Enemy(sf::RenderWindow &window, float speed, sf::Texture &texture);
    virtual ~Enemy();
    void drawEnemy(sf::RenderWindow &window);
    void updateEnemy(sf::RenderWindow &window);
    void shoot(Ship& ship);
    sf::CircleShape getMarker();
    Projectiles getProjs();
    
protected:
    sf::CircleShape markerShip;
    sf::Sprite sprite;
    float shotTime;
    sf::Texture texture;
    sf::Vector2f velocity;
    Projectiles enemyProjs;
    
private:
    
    
    
};

#endif /* Enemy_hpp */
