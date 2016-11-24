//
//  PowerUp.hpp
//  Test SFML
//
//  Created by Henry Banks on 04/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#ifndef PowerUp_hpp
#define PowerUp_hpp

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


class PowerUps : public Projectiles{
public:
    void randomPowerUp(sf::RenderWindow &window, float speed);
    void checkCollision(Ship &ship);
    PowerUps();
    void addProjSprite(sf::CircleShape newProj, float xMove, float yMove);

private:

};

#endif /* PowerUp_hpp */
