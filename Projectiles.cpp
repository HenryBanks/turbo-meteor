//
//  Projectiles.cpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Projectiles.hpp"

Projectiles::Projectiles(){
    
}

Projectiles::~Projectiles(){
    
}

void Projectiles::addProj(sf::CircleShape newProj, float xMove, float yMove){
    vecProjs.push_back(newProj);
    if (vecProjs.size()>=50){
        vecProjs.erase(vecProjs.begin());
        vecVels.erase(vecVels.begin());
    }
    std::vector<float> temp;
    temp.push_back(xMove);
    temp.push_back(yMove);
    vecVels.push_back(temp);
}

void Projectiles::drawProjs(sf::RenderWindow &window){
    for ( auto &proj : vecProjs ) {
        window.draw(proj);
    }

}

void Projectiles::updateProjs(){
    for (int i=0; i<vecProjs.size(); i++) {
        vecProjs[i].move(vecVels[i][0], vecVels[i][1]);
    }
}

std::vector<sf::CircleShape> Projectiles::getProjs(){
    return vecProjs;
}