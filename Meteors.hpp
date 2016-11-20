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
#include "Ship.hpp"


class Meteors : public Projectiles{
public:
    void randomMeteor(sf::RenderWindow &window, float speed);
    void addProjSprite(sf::CircleShape newProj, float xMove, float yMove);
    Meteors();
    
private:
    
};

#endif /* Meteors_hpp */
