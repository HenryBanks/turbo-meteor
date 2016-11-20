//
//  Ship.hpp
//  Test SFML
//
//  Created by Henry Banks on 04/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "ResourcePath.hpp"
//#include "Projectiles.hpp"
#include <random>

class Ship{
public:
    Ship();
    Ship(float xPos, float yPos);
    virtual ~Ship();
    void drawShip(sf::RenderWindow &window);
    void updateShip(sf::RenderWindow &window);
    void moveShip(sf::Event &event);
    sf::CircleShape getMarker();
    void setShotTime(float time);
    float getShotTime();
    float getMinShotTime();
    int getScore();
    void setScore(int newScore);
    int getSpeed();
    void setSpeed(int newSpeed);
    
protected:
    sf::CircleShape markerShip;
    sf::Sprite sprite;
    bool upB, downB, leftB, rightB;
    float shotTime;
    float minShotTime=0.2;
    sf::Texture texture;
    int score;
    int speed;
    
private:
    
    
    
};

#endif /* Ship_hpp */
