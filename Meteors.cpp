//
//  Meteors.cpp
//  Test SFML
//
//  Created by Henry Banks on 01/11/2016.
//  Copyright © 2016 HBanks. All rights reserved.
//

#include "Meteors.hpp"

Meteors::Meteors(){
    if (!texture.loadFromFile(resourcePath() + "c40000.png")) {
        return EXIT_FAILURE;
    }
}

void Meteors::addProjSprite(sf::CircleShape newProj, float xMove, float yMove){
    vecProjs.push_back(newProj);
    if (vecProjs.size()>=50){
        vecProjs.erase(vecProjs.begin());
        vecVels.erase(vecVels.begin());
    }
    std::vector<float> temp;
    temp.push_back(xMove);
    temp.push_back(yMove);
    vecVels.push_back(temp);
    
    sf::Sprite sprite(texture);
    sprite.setPosition(newProj.getPosition().x-2*newProj.getRadius(), newProj.getPosition().y-2*newProj.getRadius());
    //sprite.setPosition(newProj.getPosition().x, newProj.getPosition().y);
    vecSprites.push_back(sprite);
}

void Meteors::randomMeteor(sf::RenderWindow &window, float speed){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, window.getSize().x);
    float xStart, yStart, xMove, yMove;
    float xEnd, yEnd;
    xStart=dis(gen);
    xEnd=dis(gen);
    yStart=0;
    yEnd=window.getSize().y;
    xMove=xEnd-xStart;
    yMove=yEnd-yStart;
    float norm=sqrt(xMove*xMove+yMove*yMove);
    xMove=speed*xMove/norm;
    yMove=speed*yMove/norm;
    sf::CircleShape temp(20);
    temp.setFillColor(sf::Color::Red);
    temp.setPosition(xStart, yStart);
    addProjSprite(temp, xMove, yMove);
}
