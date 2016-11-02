//
//  Projectiles.hpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <vector>


#ifndef Projectiles_hpp
#define Projectiles_hpp

class Projectiles{
public:
    Projectiles();
    virtual ~Projectiles();
    void addProj(sf::CircleShape newProj, float xMove, float yMove);
    void drawProjs(sf::RenderWindow &window);
    void updateProjs();
    std::vector<sf::CircleShape> getProjs();
    
protected:
    std::vector<sf::CircleShape> vecProjs;
    std::vector<std::vector<float>> vecVels;

    
private:
    
    
    
};

#endif /* Projectiles_hpp */
