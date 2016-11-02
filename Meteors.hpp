//
//  Meteors.hpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#ifndef Meteors_hpp
#define Meteors_hpp

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


class Meteors : public Projectiles{
public:
    void randomMeteor(sf::RenderWindow &window);
    bool checkCollision(sf::CircleShape target);
    void checkCollShots(std::vector<sf::CircleShape> shotVec);
    
private:
    
};

#endif /* Meteors_hpp */
