//
//  Enemies.hpp
//  Test SFML
//
//  Created by Henry Banks on 13/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#ifndef Enemies_hpp
#define Enemies_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <vector>
#include "ResourcePath.hpp"
#include "Enemy.hpp"
#include "Ship.hpp"

class Enemies{
public:
    Enemies();
    ~Enemies();
    void drawProjsSprites(sf::RenderWindow &window);
    void updateProjsSprites(sf::RenderWindow &window, float elapsedTime);
    void addEnemy(sf::RenderWindow &window,float speed);
    void checkForDeletion(sf::RenderWindow &window);
    void shootAll(Ship &ship);
    bool checkCollision(sf::CircleShape target);
    void checkCollShots(std::vector<sf::CircleShape> shotVec, Ship &ship);

protected:
    
private:
    std::vector<Enemy> enemies;
    sf::Texture texture;
};

#endif /* Enemies_hpp */
